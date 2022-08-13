NAME		= philosopher

BONUS		= bonus_philo

SRCFILE		= ./srcs/

HEADERSFILE	= ./headers/

BONUSFILE	= ./bonus/

CC			= clang

RM			= rm -f

FLAGS		= -c -Wall -Werror -Wextra

SRCS		=	${SRCFILE}main.c \
				${SRCFILE}minilibft.c \
				${SRCFILE}philosopher.c \
				${SRCFILE}threads.c \
				${SRCFILE}utils.c \

SRCBONUS	=	${BONUSFILE}main.c \
				${BONUSFILE}child_process_check.c \
				${BONUSFILE}minilibft.c \
				${BONUSFILE}philosopher.c \
				${BONUSFILE}process_init.c\
				${BONUSFILE}utils.c\

OBJS		= ${SRCS:.c=.o}

OBJBONUS	= ${SRCBONUS:.c=.o}

all: prog bonus

${NAME}: ${OBJS}
	${CC} ${OBJS} -o $@

${BONUS}: ${OBJBONUS}
	${CC} ${OBJBONUS} -o $@

%.o : %.c
	${CC} ${FLAGS} -I ${HEADERSFILE} $< -o $@

prog: ${NAME}

bonus: ${BONUS}

clean:
	${RM} ${OBJS} ${OBJBONUS}

fclean:	clean
	${RM} ${NAME} ${BONUS}

re:	fclean all

rebonus: fclean bonus

.PHONY:	all clean fclean re rebonus prog bonus
