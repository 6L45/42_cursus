NAME		= helloBrain

CC			= clang++

FLAGS		= -Wall -Werror -Wextra -std=c++98

SRCS		=	$(SRCFILE)main.cpp\

OBJS		= $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) ${OBJS} -o $@

%.o : %.c
	$(CC) $(FLAGS) $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re
