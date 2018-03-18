# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 08:05:28 by jpriou            #+#    #+#              #
#    Updated: 2018/03/09 18:41:56 by gmonnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCDIR = src
OBJDIR = obj

SRC = \
	main.c \
	hash.c \
	utils.c \
	utils2.c \
	input.c \
	input_utils.c \
	create_line.c \
	list.c \
	op.c \
	write_file.c \
	write_file2.c \
	endian.c \
	check.c \
	check_defines.c \
	debug.c \
	fill_line.c

LIBFT_FOLDER = ../libft/
LIB = $(LIBFT_FOLDER)/libft.a \

INCDIR = includes \
		 $(LIBFT_FOLDER)/includes

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SRC))))
INCS = $(addprefix -I, $(addsuffix /, $(INCDIR)))

#Colors
_RED=$(shell tput setaf 1)
_GREEN=$(shell tput setaf 2)
_YELLOW=$(shell tput setaf 3)
_BLUE=$(shell tput setaf 4)
_PURPLE=$(shell tput setaf 5)
_CYAN=$(shell tput setaf 6)
_WHITE=$(shell tput setaf 7)
_END=$(shell tput sgr0)

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(LIB) -o $@
	@echo "$(_CYAN)Compiling project $(NAME)...$(_GREEN)DONE$(_END)"

clean:
	@echo "$(_RED)Removed objects (.o) files.$(_END)"
	@make clean -C $(LIBFT_FOLDER)
	@/bin/rm -f $(OBJS)

fclean:
	@echo "$(_RED)Removed project ($(NAME)).$(_END)"
	@make fclean -C $(LIBFT_FOLDER)
	@/bin/rm -f $(OBJS)
	@/bin/rm -f $(NAME)

re:
	make fclean
	make all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) || true
	@printf "                                                        \r"
	@printf " $(_CYAN)Compiling $@$(_END)\r"
	@$(CC) $(FLAGS) -o $@ -c $< $(INCS)

$(LIB):
	make -C $(@D) -j

.PHONY: all clean fclean re
