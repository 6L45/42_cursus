NAME		= pet

CC			= c++

HEADERSFILE	= ./

SRCFILE		= ./

FLAGS		= -Wall -Werror -Wextra -std=c++98

SRCS		=	$(SRCFILE)main.cpp\
				$(SRCFILE)animal.cpp\
				$(SRCFILE)goodPet.cpp\
				$(SRCFILE)wrongPet.cpp\

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


# NAME		= pet

# SRCS		=	$(SRCFILE)main.cpp\
# 				$(SRCFILE)animal.cpp\
# 				$(SRCFILE)goodPet.cpp\
# 				$(SRCFILE)wrongPet.cpp\

# OBJS	= $(SRCS:.cpp=.o)

# CC	= c++

# FLAGS	= -Wall -Wextra -Werror -std=c++98

# INCLUDE	= none

# HEADER	= -I./

# all : $(NAME)

# $(NAME) : $(OBJS)
# 	$(CC) -o $(NAME) $(OBJS)

# clean :
# 	rm -f $(OBJS)

# fclean : clean
# 	rm -f $(NAME)

# re : fclean all

# %.o : %.cpp
# 	$(CC) $(FLAGS) $(HEADER) -c $<  -o $(<:.cpp=.o)

# .PHONY : all clean fclean re
