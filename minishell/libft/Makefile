# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alellouc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 08:35:31 by alellouc          #+#    #+#              #
#    Updated: 2021/10/25 10:16:34 by alellouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ECHO=-echo
B_GREEN=\033[1;32m
B_RED=\033[1;31m
B_CYAN=\033[1;36m
FANCY_RESET=\033[0m
CC=-gcc
AR=-ar crs
RM=-rm -rf
MAKE=-make -s --no-print-directory
CFLAGS=-Wall -Wextra -Werror
CHEADERS=-I .
SRC=$(addprefix ft_, $(addsuffix .c,\
		memset\
		atolli\
		bzero\
		cntwds\
		memcpy\
		memccpy\
		memchr\
		memmove\
		memcmp\
		strlen\
		intlen\
		isalpha\
		isdigit\
		isalnum\
		isascii\
		isprint\
		isspace\
		isneg\
		ischarset\
		toupper\
		tolower\
		strncmp\
		strchr\
		strrchr\
		strlcpy\
		strlcat\
		strnstr\
		atoi\
		strdup\
		strndup\
		strncpy\
		calloc\
		substr\
		strjoin\
		strtrim\
		itoa\
		strmapi\
		split\
		putchar_fd\
		putstr_fd\
		putendl_fd\
		putnbr_fd\
		int_putchar_fd\
		int_putstr_fd\
		check_invalid_base\
		putnbr_base\
		luint_putnbr_base\
		basic_print\
		putlnbr_base\
		putlnbr\
		atol\
		has_valid_sign_ato\
		atol_base\
		is_int\
		swap\
		strcmp\
		lnbrcmp\
		strcpy\
		ltoa\
	))
BONUS_SRC=$(addprefix ft_, $(addsuffix .c,\
		  lstnew\
		  lstadd_front\
		  lstsize\
		  lstlast\
		  lstadd_back\
		  lstdelone\
		  lstclear\
		  lstiter\
		  lstmap\
		  print_list\
		  ))
OBJ=$(SRC:.c=.o)
BONUS_OBJ=$(BONUS_SRC:.c=.o)
NAME=libft.a

.PHONY: clean fclean re all bonus

all: $(NAME)

$(NAME): $(SRC) $(BONUS_SRC)
#	@$(ECHO) "$(B_GREEN)"
	$(CC) $(CHEADERS) $(CFLAGS) -c $^
#	@$(ECHO) "$(B_CYAN)"
	$(AR) $@ $(OBJ) $(BONUS_OBJ)
#	@$(ECHO) "$(FANCY_RESET)"
	@$(MAKE) clean
	@$(MAKE) cleanbonus

bonus: $(NAME)
#	@$(ECHO) "$(B_GREEN)"
	$(CC) $(CHEADERS) $(CFLAGS) -c $(BONUS_SRC)
#	@$(ECHO) "$(B_CYAN)"
	$(AR) $^ $(BONUS_OBJ)
#	@$(ECHO) "$(FANCY_RESET)"
	@$(MAKE) cleanbonus

clean:
#	@$(ECHO) "$(B_RED)"
	$(RM) $(OBJ)
#	@$(ECHO) "$(FANCY_RESET)"

cleanbonus: 
#	@$(ECHO) "$(B_RED)"
	$(RM) $(BONUS_OBJ)
#	@$(ECHO) "$(FANCY_RESET)"

fclean: clean cleanbonus
#	@$(ECHO) "$(B_RED)"
	$(RM) $(NAME)
#	@$(ECHO) "$(FANCY_RESET)"

re: fclean all
