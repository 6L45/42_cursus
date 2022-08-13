NAME    = libftprintf.a

SCFILE	= ./srcs/

OBJFILE	= ./header/

OBJS    = ${SRCS:.c=.o}

GCC     = gcc

RM      = rm -f

FLAGS   = -c -Wall -Wextra -Werror

SRCS    =	${SCFILE}ft_printf.c \
			${SCFILE}utils.c \
			${SCFILE}int_flag.c \
			${SCFILE}x_flag.c \
			${SCFILE}u_flag.c \
			${SCFILE}chars_flag.c \
			${SCFILE}p_flag.c \
			${SCFILE}flag_reader.c

.c.o:
	${GCC} ${FLAGS} -I ${OBJFILE} $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	ar -rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
