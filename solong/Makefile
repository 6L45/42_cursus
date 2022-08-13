NAME		= so_long

SRCFILE		= ./srcs/

HEADERSFILE	= ./headers/

OBJS		= ${SRCS:.c=.o}

GCC			= gcc

RM			= rm -f

FLAGS		= -c -Wall -Werror -Wextra

MLX			= -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

SRCS		=	${SRCFILE}main.c \
				${SRCFILE}display.c \
				${SRCFILE}key_hook.c \
				${SRCFILE}map_checker.c \
				${SRCFILE}map_reader.c \
				${SRCFILE}minilibft.c \
				${SRCFILE}utils.c \
				${SRCFILE}map_error.c \
				${SRCFILE}mvt.c \
				${SRCFILE}redraw.c \

all: prog

$(NAME): ${OBJS}
	${GCC} ${OBJS} ${MLX} -o ${NAME}

.c.o:
	${GCC} ${FLAGS} -I ${HEADERSFILE} $< -o ${<:.c=.o}

prog: ${NAME}

norme:
	norminette ${SRCS} ${HEADERSFILE}* 

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

rebonus: fclean prog bonus

.PHONY:	all clean fclean re rebonus prog bonus norme
