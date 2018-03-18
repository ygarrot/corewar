#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 11:17:30 by ygarrot           #+#    #+#              #
#    Updated: 2018/03/09 18:00:24 by jpriou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar 

FLAGS = -Wall -Werror -Wextra

SRC_FOLDER = src/

SRC_FP = main.c \
		init.c \
		parse_input.c \
		set_arena.c \
		decode_utils.c \
		erase.c \
		fetch.c \
		op.c \
		running.c \
		check_defines.c \
		manage_queue.c \
		ncurses.c \
		display_arena.c \
		check_error.c \
		display_data.c \
		fc.c \
		fc_2.c \
		fc_3.c \
		fc_4.c \

#Colors
_RED=$(shell tput setaf 1)
_GREEN=$(shell tput setaf 2)
_YELLOW=$(shell tput setaf 3)
_BLUE=$(shell tput setaf 4)
_PURPLE=$(shell tput setaf 5)
_CYAN=$(shell tput setaf 6)
_WHITE=$(shell tput setaf 7)
_END=$(shell tput sgr0)

SRC = $(addprefix $(SRC_FOLDER), $(SRC_FP))

LIBFT_FOLDER = ../libft
LIBFT = $(LIBFT_FOLDER)/libft.a

INCLUDE = -I includes/ -I $(LIBFT_FOLDER)/includes/

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $< $(INCLUDE)
	@printf "                                                        \r"
	@printf " $(_CYAN)Compiling $@$(_END)\r"

$(NAME): $(OBJ)
	@printf "                                                        \r"
	make -C $(LIBFT_FOLDER) -j
	@gcc $(FLAGS) -o $(NAME) $^ -lncurses -L $(LIBFT_FOLDER) -l ft
	@printf "                                                        \r"
	@printf "Corewar builted\n"

test: all clean

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_FOLDER) clean
	
fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@make -C $(LIBFT_FOLDER) fclean

re:
	make fclean
	make all

.PHONY: all clean fclean re
