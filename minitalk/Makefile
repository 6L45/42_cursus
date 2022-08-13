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

SERV		= server

CLT			= client

SRCSFILE	= ./srcs/

HEADERSFILE	= ./headers/

OBJSSERV	= ${SRCSERV:.c=.o}

OBJCLT		= ${SRCLT:.c=.o}

GCC			= gcc

RM			= rm -f

FLAGS		= -c -Wall -Wextra -Werror

SRCSERV		=	${SRCSFILE}server.c \
				${SRCSFILE}minilibft.c \

SRCLT		=	${SRCSFILE}minilibft.c \
				${SRCSFILE}client.c \


all: client server

${SERV}: ${OBJSSERV}
	${GCC} ${OBJSSERV} -o ${SERV}

${CLT}: ${OBJCLT}
	${GCC} ${OBJCLT} -o ${CLT}

.c.o:
	${GCC} ${FLAGS} -I ${HEADERSFILE} $< -o ${<:.c=.o}

clt: ${CLT}

serv: ${SERV}

clean:
	${RM} ${OBJSSERV} ${OBJCLT}

fclean:	clean
	${RM} ${SERV} $(CLT)

re:	fclean all

rebonus: fclean prog bonus

.PHONY:	all clean fclean re
