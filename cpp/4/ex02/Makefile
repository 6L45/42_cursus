NAME		= pet

CC			= c++

HEADERSFILE	= ./

SRCFILE		= ./

FLAGS		= -Wall -Werror -Wextra -std=c++98

SRCS		=	$(SRCFILE)main.cpp\
				$(SRCFILE)animal.cpp\
				$(SRCFILE)goodPet.cpp\
				$(SRCFILE)brain.cpp\

OBJS		= $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $@

%.o : %.cpp
	$(CC) $(FLAGS) -I$(HEADERSFILE) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
