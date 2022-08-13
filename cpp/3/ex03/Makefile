NAME		= diamongTrap

CC			= c++

HEADERSFILE	= ./

SRCFILE		= ./

FLAGS		= -Wall -Werror -Wextra -Wshadow -Wno-shadow -std=c++98

SRCS		=	$(SRCFILE)main.cpp\
				$(SRCFILE)ClapTrap.cpp\
				$(SRCFILE)FragTrap.cpp\
				$(SRCFILE)ScavTrap.cpp\
				$(SRCFILE)DiamondTrap.cpp\

OBJS		= $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $@

%.o : %.c
	$(CC) $(FLAGS) -I$(HEADERSFILE) $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
