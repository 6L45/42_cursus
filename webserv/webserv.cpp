#include "webserv.hpp"

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
	while (1)
	{
		struct sockaddr_in	addr;
		socklen_t		addr_len;

		std::cout << "waiting for connection on port " << PORT << std::endl;
		//fflush(stdout);
		this->_confd = accept(_sock, (struct sockaddr *)NULL, NULL);
		
		this->print_request_client();
		
		std::snprintf((char *)_buff, sizeof(_buff), "HTTP/1.0 200 OK\r\n\r\nHELLO WORLD!"); 
		write(_confd, (char *)_buff, strlen((char *)_buff));
		close(_confd);
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

