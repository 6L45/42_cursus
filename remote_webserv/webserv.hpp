#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdio>

#define MAXLINE 4096
#define PORT 18000

class Webserv
{
	public :
		// constru - destru
		Webserv();
		~Webserv(){};
		
		// public methods
		void 	launch();

	private :
		struct	sockaddr_in	_address;
		int			_sock;
		int			_confd;

		int			_domain;
		int			_service;
		int			_protocol;
		int			_port;
		u_long			_interface;

		char			_buff[MAXLINE + 1];
		char			*_recvline;

		// private methods
		void	print_request_client();
};

#endif

