NAME		= minishell

SRCFILE		= ./srcs/

HEADERSFILE	= ./headers/

CC			= clang

RM			= rm -f

FLAGS		= -c -Wall -Werror -Wextra

FLAGSSUP	= -L./libft -lft -lreadline -lncurses
#FLAGSSUP	= -L./libft -lft -L./libreadline -lreadline -lncurses

SRCFILE		=	./srcs/

BUILTFILE	=	${SRCFILE}builtins/
PARSEFILE	=	${SRCFILE}parsing/
UTILSFILE	=	${SRCFILE}utils/

SRCS		=	${SRCFILE}main.c\
				${SRCFILE}prompt.c\
				${SRCFILE}child_process.c\
				${SRCFILE}env.c\
				${SRCFILE}exec_cmd.c\
				${SRCFILE}heredoc_handler.c\
				${SRCFILE}multipex.c\
				${SRCFILE}signals.c\
				${SRCFILE}builtins_process.c\
				${SRCFILE}fork_processes.c\
				${BUILTFILE}builtin_cd.c\
				${BUILTFILE}builtin_echo.c\
				${BUILTFILE}builtin_env.c\
				${BUILTFILE}builtin_exit.c\
				${BUILTFILE}builtin_export.c\
				${BUILTFILE}builtin_pwd.c\
				${BUILTFILE}builtin_unset.c\
				${BUILTFILE}utils.c\
				${PARSEFILE}var_case.c\
				${PARSEFILE}lexer.c\
				${PARSEFILE}path_handler.c\
				${PARSEFILE}redir.c\
				${PARSEFILE}token_to_cmd.c\
				${PARSEFILE}tokenception.c\
				${PARSEFILE}tokenizer.c\
				${UTILSFILE}errors_print.c\
				${UTILSFILE}norminette.c\
				${UTILSFILE}parse_utils.c\
				${UTILSFILE}free.c\
				${UTILSFILE}globals.c\
				${UTILSFILE}memory_tracker.c\
				${UTILSFILE}minilibft.c\
				${UTILSFILE}utils.c\
				${UTILSFILE}env_utils.c\
				${UTILSFILE}lst_min_utils.c

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

.PHONY:	all clean fclean re rebonus prog bonus
