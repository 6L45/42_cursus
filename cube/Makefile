NAME		= cub3D

SRCFILE		= ./srcs/

HEADERSFILE	= ./headers/

CC			= clang

RM			= rm -f

FLAGS		= -Wall -Werror -Wextra -I/usr/include -Iheaders -Imlx_linux -O3 -c

FLAGSSUP	= -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRCFILE		=	./srcs/
UTLFILE		=	./utils/
PRSFILE		=	./parsing/

SRCS		=	${SRCFILE}drawing.c\
				${SRCFILE}init_str.c\
				${SRCFILE}key_press.c\
				${SRCFILE}main.c\
				${SRCFILE}minimap.c\
				${SRCFILE}mvt.c\
				${SRCFILE}raycast.c\
				${SRCFILE}render.c\
				${SRCFILE}scren_pos.c\
				${SRCFILE}srcs_utils.c\
				${UTLFILE}free.c\
				${UTLFILE}ft_color.c\
				${UTLFILE}utils.c\
				${PRSFILE}err_output.c\
				${PRSFILE}file_checker.c\
				${PRSFILE}file_handler.c\
				${PRSFILE}ft_check.c\
				${PRSFILE}get_textures.c\
				${PRSFILE}parse_utils.c\
				${PRSFILE}texture_checker.c\
				${PRSFILE}texture_utils.c\
				${PRSFILE}xpm_checker.c\

OBJ		= 		${SRCS:.c=.o}

all: prog bonus

${NAME}: ${OBJ}
	${CC} -g ${OBJ} $(FLAGSSUP) -o $@

%.o : %.c
	${CC} ${FLAGS} -I ${HEADERSFILE} $< -o $@

prog: ${NAME}

clean:
	${RM} ${OBJ}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

rebonus: fclean bonus

norme :
	norminette $(SRCFILE) $(UTLFILE) $(PRSFILE) $(HEADERSFILE)

.PHONY:	all clean fclean re rebonus prog bonus norme
