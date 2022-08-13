NAME		= push_swap

BONUS		= checker

SRCFILE		= ./srcs/

HEADERSFILE	= ./headers/

BONUSFILE	= ./bonus/

OBJS		= ${SRCS:.c=.o}

OBJBONUS	= ${SRCBONUS:.c=.o}

GCC			= clang

RM			= rm -f

FLAGS		= -c -Wall -Wextra -Werror

SRCS		=	${SRCFILE}main.c \
				${SRCFILE}act_pswap01.c \
				${SRCFILE}act_pswap02.c \
				${SRCFILE}act_pswap03.c \
				${SRCFILE}errors_entry_checker.c \
				${SRCFILE}indexed_list.c\
				${SRCFILE}minilibft.c \
				${SRCFILE}minilibft_custom.c \
				${SRCFILE}mvt_handler01.c \
				${SRCFILE}mvt_handler02.c \
				${SRCFILE}pswap_status.c \
				${SRCFILE}reorganize.c \
				${SRCFILE}solver.c \
				${SRCFILE}utils.c \
				${SRCFILE}utils_indexed_list.c \
				${SRCFILE}utils_main.c \
				${SRCFILE}utils_solver.c \
				${SRCFILE}review.c \

SRCBONUS	=	${BONUSFILE}main.c \
				${BONUSFILE}act_pswap01.c \
				${BONUSFILE}act_pswap02.c \
				${BONUSFILE}act_pswap03.c \
				${BONUSFILE}errors_entry_checker.c \
				${BONUSFILE}indexed_list.c\
				${BONUSFILE}minilibft.c \
				${BONUSFILE}minilibft_custom.c \
				${BONUSFILE}mvt_handler01.c \
				${BONUSFILE}mvt_handler02.c \
				${BONUSFILE}pswap_status.c \
				${BONUSFILE}reorganize.c \
				${BONUSFILE}solver.c \
				${BONUSFILE}utils.c \
				${BONUSFILE}utils_indexed_list.c \
				${BONUSFILE}utils_main.c \
				${BONUSFILE}utils_solver.c \
				${BONUSFILE}review.c \
				${BONUSFILE}checker.c \

all: prog bonus

$(NAME): ${OBJS}
	${GCC} ${OBJS} -o ${NAME}

$(BONUS): ${OBJBONUS}
	${GCC} ${OBJBONUS} -o ${BONUS}

.c.o:
	${GCC} ${FLAGS} -I ${HEADERSFILE} $< -o ${<:.c=.o}

prog: ${NAME}

bonus: $(BONUS)

norme:
	norminette ${SRCS} ${SRCBONUS} ${HEADERSFILE}* 

clean:
	${RM} ${OBJS} ${OBJBONUS}

fclean:	clean
	${RM} ${NAME} $(BONUS)

re:	fclean all

rebonus: fclean prog bonus

.PHONY:	all clean fclean re rebonus prog bonus norme
