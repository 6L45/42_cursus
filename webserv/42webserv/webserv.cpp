#include <arpa/inet.h>

Webserv::Webserv()
{
	this->_domain = AF_INET;
	this->_service = SOCK_STREAM;
	this->_protocol = 0;
	this->_port = PORT;
	this->_interface = INADDR_ANY;


	this->_address.sin_family = this->_domain;
	this->_address.sin_port = htons(this->_port);
	this->_address.sin_addr.s_addr = htonl(this->_interface);

	this->_sock = socket(this->_domain, this->_service, this->_protocol);
	int	flags = fcntl(this->_sock, F_GETFL);
	fcntl(this->_sock, F_SETFL, flags | O_NONBLOCK);

	if ( (bind(this->_sock, (struct sockaddr *)&(this->_address), 
					sizeof(this->_address))) < 0 )
	{
		std::cerr << "Error : bind socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	if ( (listen(this->_sock, 10)) < 0 )
	{
		std::cerr << "" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "connected and listening" << std::endl;
}

void 	Webserv::launch()
{
	struct sockaddr_in	addr;
	socklen_t			addr_len;

	while (1)
	{
		//std::cout << "waiting for connection on port " << PORT << std::endl;
		//fflush(stdout);
		this->_confd = accept(_sock, (struct sockaddr *)NULL, NULL);
		if (this->_confd == -1)
		{
			if (errno == EWOULDBLOCK)
				continue;
			else
				std::cout << "error connection" << std::endl;
		}
		else
		{
			std::cout << "Client connected at IP: " <<  inet_ntoa(this->_address.sin_addr)
				<<  " and port: " << ntohs(this->_address.sin_port) << std::endl;
			this->print_request_client();
			std::string	server_message = "HTTP/1.0 200 OK\r\n\r\nHELLO WORLD!"; 
			send(this->_confd, server_message.c_str(), server_message.length(), 0);
		// TO DO find a way to close the http response so i don't have to close the socket for it to work
		}
	}
}

void	Webserv::print_request_client()
{
	int	n;

	this->_recvline = static_cast<char *>(malloc(MAXLINE));
	memset(this->_recvline, 0, MAXLINE);
	while ( (n = read(this->_confd, this->_recvline, MAXLINE - 1)) > 0 )
	{
		std::cout << this->_recvline << std::endl << std::endl;
		if (this->_recvline[n - 1] == '\n')
			break;
	}
	if (n < 0)
	{
		std::cout << "read error" << std::endl;
		close(this->_confd);
	}
	free(this->_recvline);
}









/*
std::snprintf((char *)_buff, sizeof(_buff), "HTTP/1.0 200 OK\r\n\r\nHELLO WORLD!"); 
		write(_confd, (char *)_buff, strlen((char *)_buff));
*/