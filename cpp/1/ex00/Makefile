NAME		= zombie

CC			= clang++

HEADERSFILE	= ./

SRCFILE		= ./

FLAGS		= -Wall -Werror -Wextra -std=c++98

SRCS		=	$(SRCFILE)zombie.cpp\
				$(SRCFILE)newZombie.cpp\
				$(SRCFILE)randomChump.cpp\
				$(SRCFILE)main.cpp\

OBJS		= $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) ${OBJS} -o $@

%.o : %.c
	$(CC) $(FLAGS) -I$(HEADERSFILE) $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re
