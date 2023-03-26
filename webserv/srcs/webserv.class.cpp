#include "webserv.class.hpp"

int	g_bs = 0;

// CONSTRUCT -------------------------------------------------------------------------------
/* Unauthorized constructor */
Webserv::Webserv() {}

Webserv::Webserv(Conf config, char** env)
	:	_state(1),
		_max_connexion(config._max_connexion),
		_env(env),
		_conf(config)
{
	port_fd					socket; // opened socket
	this->_client.reserve(FD_SETSIZE + 1);
	
	for (int i = 0; i < FD_SETSIZE; i++)
	{
		t_client			deflt;
		deflt.fileno_server = true;
		deflt.fd = -1;
		this->_client.push_back(deflt);
	}

	FD_ZERO(&_current_sockets);
	FD_ZERO(&_current_write_sockets);

	for (std::vector<__server_conf>::const_iterator it = _conf._sc.begin(); it != _conf._sc.end(); it++)
	{
		Server new_server(*it, env);
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
			if (socket == -1)
				continue ;
			_track.insert(std::make_pair(it->_port, socket));
			_port_host.insert(std::make_pair(socket, it));
			FD_SET(socket, &_current_sockets);
		}
	}
	WS_DISPLAYON;
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
	if ( (listen(new_socket, 1000)) == -1 ) // <--- second arg = backlog : defines the maximum length to which the queue of pending connections for sockfd may grow
	{
		std::cerr << "-- listen error : unable to listen on the socket -> port " << port << " is not connected" << std::endl;
		close (new_socket);
		return (-1);
	}

	this->_fd_tracker.insert(new_socket);
	return (new_socket);
}

Webserv::~Webserv()
{
	for (std::list<Client>::const_iterator c_it = _clients.begin(); c_it != _clients.end(); c_it++)
		close(c_it->_fd);
	_clients.clear(); // NOT needed
	for (std::map<int,port_fd>::const_iterator c_it = _track.begin(); c_it != _track.end(); c_it++)
		close(c_it->second);
	FD_ZERO(&_current_sockets); // just in case
	FD_ZERO(&_current_write_sockets); // just in case
	__display_endl("++ closing the webserver ++", std::cout);
	__display_endl("If you enjoyed the experience, please donate on Paypal to @webservteam42", std::cout);
}
// ------------------------------------------------------------------------------------------











// SOCKETS MECHANICS -----------------------------------------------------------------------
void 	Webserv::launch()
{
	struct sockaddr_in	client;
	socklen_t		client_len = sizeof(struct sockaddr_in);
	fd_set			ready_sockets;
	fd_set			ready_write_sockets;
	int			select_ret;
	int			write = -1;
	struct timeval		tempo;


	tempo.tv_sec = 0;
	tempo.tv_usec = 1;
	
	/* Listening to STDIN for console manipulations */
	FD_SET(STDIN_FILENO, &_current_sockets);
	if (this->_fd_tracker.empty())
		WS_SETEND;
	while (WS_ISRUNNING)
	{
		if (write == -1)
			__display_endl("++ waiting for connections ++", std::cout);
		FD_ZERO(&ready_sockets);
		FD_ZERO(&ready_write_sockets);
		if (WS_ISINPAUSE)
			FD_SET(STDIN_FILENO, &ready_sockets);
		else
		{
			ready_sockets = _current_sockets;
			ready_write_sockets = _current_write_sockets;
		}

		select_ret = select(FD_SETSIZE, &ready_sockets, &ready_write_sockets, NULL, &tempo);
		if (select_ret < 0)
		{
			perror("fatal error : select");
			break ;
		}
		if (select_ret == 0)
		{
			write = 1;
			__timeout_handler();
			continue ;
		}
		write = -1;
		__check_sockets(ready_sockets, ready_write_sockets, client, client_len);	
	}
}

void	Webserv::__timeout_handler()
{
	for (std::vector<t_client>::iterator it = this->_client.begin();
			it != this->_client.end(); it++)
	{
		if (it->fd > 0 && !it->fileno_server)
		{
			clock_t	now = std::clock();
			if (((now - it->t) / CLOCKS_PER_SEC) > it->keep_alive)
			{
				if (it->request_handler != NULL
					&& it->request_handler->awaiting_fd_for_writing().first > 0)
				{
					FD_CLR(it->request_handler->awaiting_fd_for_writing().first, &_current_sockets);
					FD_CLR(it->request_handler->awaiting_fd_for_writing().second, &_current_sockets);

					close(it->request_handler->awaiting_fd_for_writing().first);
					close(it->request_handler->awaiting_fd_for_writing().second);

					this->_fd_tracker.erase(it->request_handler->awaiting_fd_for_writing().first);
					this->_fd_tracker.erase(it->request_handler->awaiting_fd_for_writing().second);
				}
			
				send_response(it->fd, Http_handler::http_408());

				delete it->request_handler;
				it->request_handler = NULL;
			}
		}
	}
}

void	Webserv::__check_sockets(fd_set &ready_sockets, fd_set &ready_write_sockets,struct sockaddr_in &client, socklen_t &client_len)
{
	for (int i = 0; i <= *this->_fd_tracker.rbegin(); i++)
	{
		if (FD_ISSET(i, &ready_write_sockets))
		{
			send_response(i);
		}
		
		if (FD_ISSET(i, &ready_sockets))
		{
			/*
				New Connexion
			*/
			if (this->__is_a_socket(i))
			{
				__display("++ Connexion request on socket port : ", std::cout);
				__display(__get_the_port(i), std::cout);
				__display_endl(" ++", std::cout);
				port_fd fd = accept(i, (SA *)&client, &client_len);
				this->__new_connect_init(fd, i);	
			}
			/*
				Input on the consol by admin user
			*/
			else if (i == STDIN_FILENO)
				this->__console();
			/*

			*/
			else if (_corresponding_cgi_fd.find(i) != _corresponding_cgi_fd.end() 
				&& this->_client[_corresponding_cgi_fd[i]].request_handler != NULL)
			{
				// les fds dans fd writes sont les fd open pour le cgi
				// corresponding_cgi_fd est un map<int, int> pour faire correspondre les fd opens au fd socket
				int	cgi_fd = _corresponding_cgi_fd[i];

				// get le resulta du cgi
				std::string	response =  this->_client[cgi_fd].request_handler->cgi_response();
				
				// si le cgi n'a pas encore terminé on ignore (cgi_response sera vide si c'est le cas)
				// std::cout << "cgi _triggered" << std::endl;
				if (response.empty())
					continue;
				// clean vector
				_corresponding_cgi_fd.erase(this->_client[cgi_fd].request_handler->awaiting_fd_for_writing().first);
				_corresponding_cgi_fd.erase(this->_client[cgi_fd].request_handler->awaiting_fd_for_writing().second);

				// send response
				send_response(this->_client[cgi_fd].request_handler->get_fd_response(), response);

				// clear fd writes
				FD_CLR(this->_client[cgi_fd].request_handler->awaiting_fd_for_writing().first, &_current_sockets);
				FD_CLR(this->_client[cgi_fd].request_handler->awaiting_fd_for_writing().second, &_current_sockets);

				// les deux fd open (awaiting fd for writing retourne un pair)	
				close(this->_client[cgi_fd].request_handler->awaiting_fd_for_writing().first);
				close(this->_client[cgi_fd].request_handler->awaiting_fd_for_writing().second);

				this->_fd_tracker.erase(this->_client[cgi_fd].request_handler->awaiting_fd_for_writing().first);
				this->_fd_tracker.erase(this->_client[cgi_fd].request_handler->awaiting_fd_for_writing().second);
			}
			else if (__get_the_port(i) > 0)
			{
				__display("++ client request on port : ", std::cout);
				__display(__get_the_port(i), std::cout);
				__display_endl(" ++", std::cout);
				request_handler(i);
			}
		}
	}
}

// cut from main loop
void	Webserv::__new_connect_init(int fd, int i)
{
	if (fd == -1)
	{
		std::cerr << "-- accept error : failed to accept the connexion on the port " << __get_the_port(i) << std::endl;
		return ;
	}
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "-- Fcntl error : unable to make the client file descriptor non blocking -> connexion non accepted " << std::endl;
		close (fd);
		return ;
	}

	_clients.push_back(Client(fd,__get_the_port(i),0));
	FD_SET(fd, &_current_sockets);
	__display_endl("++ Connexion accepted ++", std::cout);

	this->_fd_tracker.insert(fd);
	this->_client[fd].fd = fd;
	this->_client[fd].fileno_server = false;
	this->_client[fd].t = std::clock();
	this->_client[fd].keep_alive = KEEP_ALIVE;
	this->_client[fd].request_handler = NULL;
}

void	Webserv::__close_connexion(const int fd)
{
	close(fd);

	FD_CLR(fd, &_current_sockets);
	FD_CLR(fd, &_current_write_sockets);

	this->_client[fd].request.clear();
	this->_client[fd].response.clear();
	this->_client[fd].chunk.clear();
	this->_client[fd].fd = -1;
	if (this->_client[fd].request_handler != NULL)
	{
		delete this->_client[fd].request_handler;
		this->_client[fd].request_handler = NULL;
	}
	
	for (std::list<Client>::const_iterator c_it = _clients.begin(); c_it != _clients.end(); c_it++)
	{
		if (c_it->_fd == fd)
		{
			_clients.erase(c_it);
			break ;
		}
	}
	__display("++ connexion closed on fd : ", std::cout);
	__display(fd, std::cout);
	__display_endl( " ++", std::cout);
	
	this->_fd_tracker.erase(fd);
}
// -----------------------------------------------------------------------------------------











// HTTP ------------------------------------------------------------------------------------
int	Webserv::__http_handler_init(int fd)
{
	int	ret;
			
	this->_client[fd].request_handler = new Http_handler(this->_client[fd].request, fd); // chunked construct

	if ( (ret = this->_client[fd].request_handler->invalid_request())!= 0) 
	{
		return ret;
	}
	// find associated server
	std::string	host_port = this->_client[fd].request_handler->get_host_name();
	std::vector<Server>::iterator	it;
	for (it = _servers.begin(); it != _servers.end(); it++)
	{
		if ((*it).belong_to(host_port))
			break ;
	}
	// if host doesnt exist
	if (it == _servers.end())
	{
		std::cout << "Host doesnt exist -> " << host_port << std::endl;
		this->_client[fd].request.clear();
		return 400;
	}

	// set up loc pour recup method autorisée et body size limit si loc == NULL return 404
	if ( (ret = this->_client[fd].request_handler->unauthorized_method(*it)) != 0)
	{
		this->_client[fd].request.clear();
		return ret;
	}

	return 0;
}

void	Webserv::request_handler(int fd)
{
	std::vector<char>	buff(MAXLINE); // C++ version
	int					n;

	n = recv(fd, buff.data(), MAXLINE - 1, 0);

	if (n == 0)
	{
		__display_endl("++ Connexion is closed on the client side ++", std::cout);
		return (__close_connexion(fd));
	}
	else if (n < 0)
	{
		// if (errno != EAGAIN)
		// {
			std::cerr << "-- recv error : something went wrong when recieving message -> client disconnected " << std::endl;
			return (__close_connexion(fd));
		// }
	}

	std::string	request(buff.data());
	buff.clear();
	//std::cout << "RAW REQUEST" << std::endl << request << std::endl << "-----------" << std::endl;
	// if request received (or stocked in client) got (chunked OR Chunked) AND Transfer-Encoding
	if (( (this->_client[fd].request.find("chunked") != std::string::npos
					|| this->_client[fd].request.find("Chunked") != std::string::npos)
				&& this->_client[fd].request.find("Transfer-Encoding:") != std::string::npos)
		|| ( (request.find("chunked") != std::string::npos
					|| request.find("Chunked") != std::string::npos)
				&& request.find("Transfer-Encoding:") != std::string::npos))
	{
		// if \r\n\r\n missing - header unfinished => stock and wait
		if (this->_client[fd].request.find("\r\n\r\n") == std::string::npos)
		{
			size_t	pos;
			if ( (pos = request.find("\r\n\r\n")) != std::string::npos )
			{
				this->_client[fd].request += request.substr(0, pos + 4);
				request = request.substr(pos + 4);
			}
			else
				this->_client[fd].request += request;

			if (this->_client[fd].request.find("\r\n\r\n") == std::string::npos)
				return;
		}

		// if no request handler yet
		if (this->_client[fd].request_handler == NULL)
		{
			int	err;
			if ( (err = __http_handler_init(fd)) > 0)
			{
				return __response_XXX_and_close(fd, err);
			}
		} 

		// concat + check if size doesn't go further than authorized
		int ret = this->_client[fd].chunk.concat(request);

		this->_client[fd].t = std::clock();
		
		if (ret > 0) // everything's OK chunks not over
			return;
		else if (ret == 0) // everything's OK chunks over
			this->_client[fd].request_handler->add_body(this->_client[fd].chunk.get_full_body());
		else if (this->_client[fd].request_handler == NULL) // error 400 Bad Request
		{
			return __response_XXX_and_close(fd, 400);
		}
	}

	// if \r\n\r\n missing - header unfinished => stock and wait
	else if (request.find("\r\n\r\n") == std::string::npos || !this->_client[fd].request.empty())
	{
		this->_client[fd].request += request;
		if (this->_client[fd].request.find("\r\n\r\n") == std::string::npos)
			return;
	}
	else
		this->_client[fd].request = request;

	if ( ((this->_client[fd].request.find("chunked") != std::string::npos
					|| this->_client[fd].request.find("Chunked") != std::string::npos)
				&& this->_client[fd].request.find("Transfer-Encoding:") != std::string::npos)
		&& this->_client[fd].request_handler == NULL)
	{
		return;
	}

	// INUTILE MAIS AU CAS OU, PEUT SERVIR PLUS TARD
/*	if (this->_client[fd].request_handler != NULL
		&& this->_client[fd].request_handler->get_content_length_val() > 0
		&& this->_client[fd].request_handler->get_body().length()
			< this->_client[fd].request_handler->get_content_length_val())
		return; */

	this->_client[fd].chunk.clear();
	__http_process(fd, this->_client[fd].request);
}

void	Webserv::__http_process(int fd, std::string &request)
{
	std::string		response;

	if (this->_client[fd].request_handler == NULL)
	{
		int err;
		if ( (err = __http_handler_init(fd)))
		{
			return __response_XXX_and_close(fd, err);
		}
		this->_client[fd].request_handler->load_body(request);
	}

	//SIZE CHECKER
	if (this->_client[fd].request_handler->body_max_size() > 0
		&& this->_client[fd].request_handler->get_body().length()
			> this->_client[fd].request_handler->body_max_size())
	{
		// std::cout << this->_client[fd].request_handler->body_max_size() << std::endl;
		return __response_XXX_and_close(fd, 413);
	}

	//PIPELINE HANDLER
	if (this->_client[fd].request_handler->body_inspector().first)
	{
		this->_client[fd].pipeline = this->_client[fd].request_handler->body_inspector().second;
		this->_client[fd].request_handler->pipelined_body_destroy();
	}
	__http_execution(fd);
}

void	Webserv::__pipeline_handler(int fd)
{
	this->_client[fd].request.clear();
	this->_client[fd].response.clear();
	this->_client[fd].chunk.clear();

	delete this->_client[fd].request_handler;
	
	this->_client[fd].request.swap(this->_client[fd].pipeline[0]);

	int	err;
	if ( (err = __http_handler_init(fd)))
	{
		__response_XXX_and_close(fd, err);
	}
	else
	{
		__http_execution(fd);
	}
	this->_client[fd].pipeline.erase(this->_client[fd].pipeline.begin());
}

void	Webserv::__cgi_fds_init(int fd)
{
	int fd1 = this->_client[fd].request_handler->awaiting_fd_for_writing().first;
	int fd2 = this->_client[fd].request_handler->awaiting_fd_for_writing().second;
	FD_SET(fd1, &_current_sockets);
	FD_SET(fd2, &_current_sockets);
	
	_corresponding_cgi_fd[fd1] = fd;
	_corresponding_cgi_fd[fd2] = fd;

	this->_fd_tracker.insert(fd1);
	this->_fd_tracker.insert(fd2);
}

void	Webserv::__http_execution(int fd)
{
	this->_client[fd].response = this->_client[fd].request_handler->exec_request();

	// Si il y'a les fd générés par cgi alors placer les fd dans fd write à surveiller
	// et retour en attendant réponse du cgi
	if (this->_client[fd].request_handler->awaiting_fd_for_writing().first > 0)
		return __cgi_fds_init(fd);

	//keep alive or close values are set here
	if (this->_client[fd].request_handler->get_keep_alive())
	{
		this->_client[fd].keep_alive = std::min(this->_client[fd].request_handler->keep_alive_value(), KEEP_ALIVE);
		this->_client[fd].t = std::clock();
	}	
	else if (this->_client[fd].request_handler->get_connection().compare("null")) // if connection field doesn't return null
	{
		if ((!this->_client[fd].request_handler->get_connection().compare("keep-alive"))
				|| !this->_client[fd].request_handler->get_connection().compare("Keep-Alive"))
		{
			this->_client[fd].keep_alive = KEEP_ALIVE;
			this->_client[fd].t = std::clock();
		}
	}

	send_response(fd, this->_client[fd].response);
}
// -----------------------------------------------------------------------------------------











// COM IN - OUT ----------------------------------------------------------------------------
/*
	Send_response (fd && response) : Set everything for futur select
	On save la réponse a envoyer dans la structure du client
	On ajoute le fd du client dans la liste des WRITE_SOCKETS
*/
void	Webserv::send_response(int fd, const std::string& response)
{
	__display_endl("---------------- response server : ----------------", std::cout);
	// __display_endl(response, std::cout);
	__display_endl(response.substr(0, response.find("\r\n\r\n") + 4) + "<", std::cout);
	__display_endl("---------------- -------------- ----------------", std::cout);
	this->_client[fd].response = response;
	FD_SET(fd, &_current_write_sockets);
	FD_CLR(fd, &_current_sockets);

	this->_client[fd].t = std::clock();
}

/*
	send_response (FD) trigger par le select
	On write, on supprime la partie ecrite. 
	Tant que la response n'est pas empty() on laisse le FD dans la liste des WRITE_SOCKETS

	Si fin du message, check si keep_alive et close du fd dans le cas contraire
*/
void	Webserv::send_response(int fd)
{
	int	ret;
	std::signal(SIGPIPE, SIG_IGN);

	ret = send(fd, this->_client[fd].response.data(), this->_client[fd].response.length(), 0);
	this->_client[fd].t = std::clock();

	if (ret < 0)// && (errno == EPIPE))
	{
		__display_endl("++connexion with client is lost++", std::cout);
		return (__close_connexion(fd));
	}
	if (ret >= 0)
	{
		this->_client[fd].response.erase(0, ret);
	}
	if (this->_client[fd].response.empty())
		FD_CLR(fd, &_current_write_sockets);

	__display("Message send to the client on port : ", std::cout);
	__display(__get_the_port(fd), std::cout);
	__display_endl("++", std::cout);
	__display("bytes manquants pas encore envoyees : ", std::cout);
	__display_endl(this->_client[fd].response.length(), std::cout);

	/*
		On ferme la connexion si
		** le message a envoyé est terminé
		** il n'y a pas de request_handlers (ce qui veut dire qu'il s'agit d'un envoi vers le cgi)
		** le keep_alive n'est pas demandé dans la requete, la connexion est en mode close
	*/

	if (this->_client[fd].pipeline.size() > 0)
	{
		this->__pipeline_handler(fd);
	}
	if (this->_client[fd].response.empty())
	{
		FD_CLR(fd, &_current_write_sockets);
		FD_SET(fd, &_current_sockets);
	}
	if (this->_client[fd].response.empty()
		&&  (this->_client[fd].request_handler == NULL 
				|| (! this->_client[fd].request_handler->get_keep_alive() //							if request had a keep alive field
					|| !this->_client[fd].request_handler->get_connection().compare("keep-alive") //				OR this connection field have a keep-alive value
					|| !this->_client[fd].request_handler->get_connection().compare("Keep-Alive"))))	//			OR a Keep-Alive value
	{
		__close_connexion(fd);												//	close connect
	}
}

void	Webserv::__response_XXX_and_close(int fd, int ret)
{
	if (ret >= 300 && ret < 400)
		send_response(fd, Http_handler::http_XXX(ret, this->_client[fd].request_handler->get_alternates_path()));
	else
		send_response(fd, Http_handler::http_XXX(ret, "", this->_conf._default_error_root));
}
// -----------------------------------------------------------------------------------------











// UTILS -----------------------------------------------------------------------------------
bool is_digits(const std::string &str)
{
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (!std::isdigit(*it))
			return false;
	}
	return true;
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
	else if (!cmd.compare(0, 4, "stat"))
		__print_connexions_stats();
	else if ((!cmd.compare(0, 6, "dspoff")))
		WS_DISPLAYOFF;
	else if ((!cmd.compare(0, 6, "dspon")))
		WS_DISPLAYON;
	else if ((!cmd.compare(0, 6, "size")))
	{
		std::cout << "vector _client - " << this->_client.size() << std::endl;
		std::cout << "map _corresponding_cgi_fd - " << this->_corresponding_cgi_fd.size() << std::endl;
		std::cout << "multimap _port_host - " << this->_port_host.size() << std::endl;
		std::cout << "map _track - " << this->_track.size() << std::endl;
		std::cout << "vector _servers - " << this->_servers.size() << std::endl;
		std::cout << "list _clients - " << this->_clients.size() << std::endl;
	}
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

template <class T>
void	Webserv::__display(const T& msg, std::ostream& o)
{
	if (WS_DISPLAY)
		o << msg;
}

template <class T>
void	Webserv::__display_endl(const T& msg, std::ostream& o)
{
	if (WS_DISPLAY)
		o << msg << std::endl;
}
// -----------------------------------------------------------------------------------------











// CHUNKS ----------------------------------------------------------------------------------
Chunks::Chunks() : _size(0) {}

bool	Chunks::__eraseFirstLine(std::string &s)
{
	std::string::iterator it = s.begin();
	while (it != s.end() && (*it == '\r' || *it == '\n'))
		it = s.erase(it);
	return it != s.begin();
}

int	Chunks::concat(std::string &request)
{
	// office de log pour suivre la ou ça pourrait planter
	// std::ofstream	file;
	// file.open("res", std::ios_base::app);

	/* on travail sur un buffer car il y a un cas où on doit attendre la fin de la ligne de la requete avant de faire des calculs de hexa*/
	this->_buffer += request;
	/* la request est save dans buffer, on en a plus besoin */
	request.erase();
	/* On supprime les /r/n du debut */
	__eraseFirstLine(this->_buffer);
	/* request ne contanait que le /r/n */
	if (this->_buffer.empty())
		return (1);
	/* Si le chunk precedent n'est pas complet, on doit le completer avec le contenu de request */
	if (this->_size != 0)
	{
		// file << "----------------------------------------------------------------" << std::endl;
		// file << "the size is " << this->_size << std::endl;
		int min = std::min(this->_size, static_cast<int>(this->_buffer.length()));
		// file << "min is calculated : " << min << std::endl;
		this->_body += this->_buffer.substr(0, min);
		// file << "new body size : " << this->_body.size() << std::endl; 
		this->_buffer.erase(0,min);
		this->_size -= min;
		// file << "new size after concat : " << this->_size << std::endl;
		// file << "----------------------------------------------------------------" << std::endl;
		// file.close();
		return (concat(request));
	}
	/* Si le chunk precedent est complet, request est le debut d'un chunk */
	else
	{
		// file << "----------------------------------------------------------------" << std::endl;
		// file << "the size is " << this->_size << std::endl;
		/* we should wait until the end of line of hexa data line is recieved */
		if (this->_buffer.find_first_of("\r\n") == std::string::npos)
		{
			// file << "hexa line is not compleat. Waiting" << std::endl;
			// file << "----------------------------------------------------------------" << std::endl;
			return (1);
		}
		this->_size = __hex_string_to_int(this->_buffer.substr(0, this->_buffer.find_first_of("\r\n")));
		// file << "the new size after hex calculation is " << this->_size << std::endl;
		/* Si taille 0, fin des chunks */
		if (this->_size == 0)
		{
			if (this->_body.empty())
				return -1;
			return 0;
		}
		if (this->_size < 0)
			return -1;
		/* Sinon recurence sur request */
		// file << "erasing hex from request" << std::endl;
		this->_buffer.erase(0, this->_buffer.find_first_of("\r\n") + 2);
		// file << "call concat" << std::endl;
		// file << "----------------------------------------------------------------" << std::endl;
		// file.close();
		return (concat(request));
	}
}

std::string	&Chunks::get_full_body() {
	return (this->_body);
}

int	Chunks::get_body_size(){
	return (this->_body.length());
}

void	Chunks::clear()
{
	this->_size = 0;
	this->_body.clear();
	this->_buffer.clear();
}

int	Chunks::__hex_string_to_int(const std::string &hex_string)
{
	int					result;
	std::stringstream	ss;

	ss << std::hex << hex_string;
	ss >> result;

	if (ss.fail())
		return (-1);
	return result;
}









































// A revoir || déplacer le size n'a l'air d'être pour réponse uniquement pas pour reception
/*
		if (this->_client[fd].request_handler->body_max_size()
			&& this->_client[fd].chunk.get_body_size() > this->_client[fd].request_handler->body_max_size())
		{
			this->_client[fd].request.clear();
			this->_client[fd].chunk.clear();

			return __response_XXX_and_close(fd, g_bs);
		}
*/	
