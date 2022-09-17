# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberengu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 16:20:03 by mberengu          #+#    #+#              #
#    Updated: 2021/09/24 16:20:05 by mberengu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERV			= server

CLT				= client

SRCSFILESERV	= ./server_files/

SRCSFILECLT		= ./client_files/

HEADERASIO		= $(HOME)/bin/boost_1_80_0/
HEADERFILE		= ./headers

CC				= g++

RM				= rm -f

FLAGS			= -c

SRCSERV			=	$(SRCSFILESERV)server.cpp \

SRCLT			=	$(SRCSFILECLT)client.cpp \

OBJSSERV		= $(SRCSERV:.cpp=.o)

OBJCLT			= $(SRCLT:.cpp=.o)


all: clt serv

$(SERV): $(OBJSSERV)
	$(CC) $(OBJSSERV) -o $@

$(CLT): $(OBJCLT)
	$(CC) $(OBJCLT) -o $@

.cpp.o:
	$(CC) $(FLAGS) -I$(HEADERASIO) -I$(HEADERFILE) $< -o $@

clt: $(CLT)

serv: $(SERV)

clean:
	$(RM) $(OBJSSERV) $(OBJCLT)

fclean:	clean
	$(RM) $(SERV) $(CLT)

re:	fclean all

rebonus: fclean prog bonus

.PHONY:	all clean fclean re
