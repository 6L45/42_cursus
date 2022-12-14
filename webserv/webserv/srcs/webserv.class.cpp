#include "webserv.class.hpp"

Webserv::Webserv(Conf config)
	:	_state(1),
		_conf(config)
{
	// Les servers seront à initialiser les serveurs en fonction du fichier conf
//	Server	empty_serv;
	// Server	server1(PORT);
	// Server	server2(SERVER_PORT);

	// // stock provisoirement dans tmp;
	// std::vector<Server> tmp;
	// tmp.push_back(server1);
	// tmp.push_back(server2);

	// int i = 0;
	// int	fd_max = 0;
	// // chercher le plus grand FD ouvert pour la taille de reserve	
	// for (std::vector<Server>::iterator it = tmp.begin(); it != tmp.end(); it++, i++)
	// {
	// 	if (tmp[i].get_socket() > fd_max)
	// 		fd_max = tmp[i].get_socket();
	// }
	// this->_servs.reserve(fd_max + 1);
	
	// i = 0;
	// int j = 0;
	// for (std::vector<Server>::iterator it = tmp.begin(); it != tmp.end(); it++, i++)
	// {
	// 	while (tmp[i].get_socket() != j)
	// 		j++;
	// 	this->_servs[j] = tmp[i];
	// 	this->_server_fd.push_back(tmp[i].get_socket());
	// 	j = 0;
	// }
	//########################
	port_fd					socket; // opened socket

	FD_ZERO(&_current_sockets);

	for (std::vector<__server_conf>::const_iterator it = _conf._sc.begin(); it != _conf._sc.end(); it++)
	{
		Server new_server(*it);
		_servers.push_back(new_server);
	}
	for (std::vector<Server>::const_iterator it = _servers.begin(); it != _servers.end(); it++)
	{
		std::map<int,port_fd>::const_iterator it_track = _track.find(it->_port);
		/*
			if ()
				the socket on the listener port of this server is already opened (by a previous server using the same port)
				Adding only port-server in multimap
			else ()
				we create the new socket on the selected port and adding it on the map track, the fd_set, and in multimap port-server
		*/
		if (it_track != _track.end())
			_port_host.insert(std::make_pair(it_track->second, it));
		else
		{
			socket = __create_socket(it->_port);
			_track.insert(std::make_pair(it->_port, socket));
			_port_host.insert(std::make_pair(socket, it));
			FD_SET(socket, &_current_sockets);
		}
	}
}

Webserv::port_fd	Webserv::__create_socket(int port)
{
	struct	sockaddr_in	address;
	port_fd				new_socket;

	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	// socket creation 
	new_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (new_socket == -1)
	{
		std::cerr << "-- Socket error : unable to create the socket -> port " << port << " is not connected" << std::endl;
		return (-1);
	}
	// set the socket to a non blocking state
	if (fcntl(new_socket, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "-- Fcntl error : unable to make the socket non blocking -> port " << port << " is not connected" << std::endl;
		close (new_socket);
		return (-1);
	}
	// bind the socket to accept connexions
	if ( (bind(new_socket, (struct sockaddr *)&(address), sizeof(address))) == -1 )
	{
		std::cerr << "-- bind error : unable to bind the socket to the port -> port " << port << " is not connected" << std::endl;
		close (new_socket);
		return (-1);
	}
	// listen to the port
	if ( (listen(new_socket, 30)) == -1 ) // <--- second arg = backlog : defines the maximum length to which the queue of pending connections for sockfd may grow
	{
		std::cerr << "-- listen error : unable to listen on the socket -> port " << port << " is not connected" << std::endl;
		close (new_socket);
		return (-1);
	}
	return (new_socket);
}

/* Unauthorized constructor */
Webserv::Webserv()
{ }

Webserv::~Webserv()
{
	for (std::list<Client>::const_iterator c_it = _clients.begin(); c_it != _clients.end(); c_it++)
		close(c_it->_fd);
	_clients.clear(); // NOT needed
	for (std::map<int,port_fd>::const_iterator c_it = _track.begin(); c_it != _track.end(); c_it++)
		close(c_it->second);
	FD_ZERO(&_current_sockets); // just in case
}

void 	Webserv::launch()
{
	struct sockaddr_in	client;
	socklen_t			client_len;
	fd_set				ready_sockets;
	port_fd				fd;
/*	struct timeval		tempo;

	tempo.tv_sec = 0;
	tempo.tv_usec = 1;
*/
//	uint16_t			conn_port;
	client_len = sizeof(client);
	FD_SET(STDIN_FILENO, &_current_sockets); //listening to the stdin for console manipulations

	while (WS_ISRUNNING)
	{
		std::cout << "++ waiting for connection ++" << std::endl; 
		if (WS_ISINPAUSE)
		{
			FD_ZERO(&ready_sockets);
			FD_SET(STDIN_FILENO, &ready_sockets);
		}
		else
			ready_sockets = _current_sockets;
		if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
		{
			perror("select error");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &ready_sockets))
			{
				if (this->__is_a_socket(i))
				{
					std::cout << "++ Connexion request on socket port : " << __get_the_port(i) << " ++" << std::endl;
					fd = accept(i, (SA *)&client, &client_len);
					if (fd == -1)
					{
						std::cerr << "-- accept error : failed to accept the connexion on the port " << __get_the_port(i) << std::endl;
						continue ;
					}
					if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
					{
						std::cerr << "-- Fcntl error : unable to make the client file descriptor non blocking -> connexion non accepted " << std::endl;
						close (fd);
						continue ;
					}
					_clients.push_back(Client(fd,__get_the_port(i),0));
					FD_SET(fd, &_current_sockets);
					std::cout << "++ Connexion accepted ++" << std::endl;
					
					// this->_fds.insert(std::pair<int, int>(this->_confd, i));
//					std::cout << "sin_port : " << ntohs(client.sin_port) << std::endl;
//					std::cout << "sin_addr : " << ntohs(client.sin_addr.s_addr) << std::endl;
				}
				else if (i == STDIN_FILENO)
					this->__console();
				else
				{
					std::cout << "++ client request on port : " << __get_the_port(i) << " ++" << std::endl;
					
					// peut être update par une seule fonction du genre "request handler"
					request_handler(i);
				}	
			}
		}
	}
}

void	Webserv::__close_connexion(int fd)
{
	std::cout << "++ Connexion is closed on the client side ++" << std::endl;
	close(fd);
	for (std::list<Client>::const_iterator c_it = _clients.begin(); c_it != _clients.end(); c_it++)
	{
		if (c_it->_fd == fd)
		{
			_clients.erase(c_it);
			break ;
		}
	}
	FD_CLR(fd, &_current_sockets);
}

int		Webserv::__get_the_port(int fd)
{
	for (std::map<int,port_fd>::const_iterator c_it = _track.begin(); c_it != _track.end(); c_it++)
	{
		if (c_it->second == fd)
			return (c_it->first);
	}
	for (std::list<Client>::const_iterator c_it = _clients.begin(); c_it != _clients.end(); c_it++)
	{
		if (c_it->_fd == fd)
			 return (c_it->_port);
	}
	return (-1);
}

void	Webserv::request_handler(int fd)
{
	int	n;

	std::vector<char> buff(MAXLINE); // C++ version

	std::cout << std::endl;
	//while ( > 0);
	n = recv(fd, buff.data(), buff.size(), 0);
	if (n == 0)
		return (__close_connexion(fd));
	else if (n < 0 && errno != EAGAIN)
	{
		std::cerr << "-- recv error : something went wrong when recieving message -> client disconnected " << std::endl;
		return (__close_connexion(fd));
	}
	std::string	request(buff.data());
	std::cout << "++ Here the client request ->" << std::endl;
	std::cout << request << std::endl;

	//Http_handler request_handler(request);
	_servers.begin()->send_response(fd, _current_sockets); //peu importe quel serveur repond la reponse est la même.
	//sinon pour la suite ajouter une fonction qui check vers quel serveur se tourner selon le host de la requete.
}

bool	Webserv::__is_a_socket(int fd) const
{
	/* 
		A file descriptor is an opened socket on listening port is 
		the key argument in multimap port-host
	*/
	return (_port_host.find(fd) != _port_host.end());
}

void	Webserv::__console()
{
	std::string cmd;
	std::string cmd_to_compare;

	std::getline(std::cin, cmd);
	if (!cmd.compare(0, (cmd_to_compare = CMD_END_WEBSERV).size(), CMD_END_WEBSERV))
		WS_SETEND;
	else if (!cmd.compare(0, (cmd_to_compare = CMD_PAUSE).size(), CMD_PAUSE))
		WS_SETPAUSE;
	else if (!cmd.compare(0, (cmd_to_compare = CMD_RUN).size(), CMD_RUN))
		WS_SETUNPAUSE;
	else if (!cmd.compare(0, 4, "stat"))
		__print_connexions_stats();
}


void	Webserv::__print_connexions_stats() const
{
	std::cout << "Sockets (port,fd) : ";
	for (std::map<int,port_fd>::const_iterator c_it = _track.begin(); c_it != _track.end(); c_it++)
		std::cout << "( " << c_it->first << " , " << c_it->second << " ) ";
	std::cout << std::endl;
	std::cout << "Clients connected (port,fd) : ";
	for (std::list<Client>::const_iterator c_it = _clients.begin(); c_it != _clients.end(); c_it++)
		std::cout << "( " << c_it->_port << " , " << c_it->_fd << " ) ";
	std::cout << std::endl;
}








// au cas ou j'en aurai besoin à un moment ou un autre
// permet de récupérer le port de connection de client

//					getsockname(fd, (SA *)&client, &client_len);
//					conn_port = ntohs(client.sin_port);

