# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fauconfan <fauconfan@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/01 10:57:31 by jpriou            #+#    #+#              #
#    Updated: 2018/03/18 10:28:33 by jpriou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_DIR = asm_dir/
VM_DIR = vm_dir/

ASM = $(ASM_DIR)asm
VM = $(VM_DIR)corewar

NAME = $(ASM) $(VM)

all : $(NAME)

$(ASM) :
	make -C $(ASM_DIR)

$(VM) :
	make -C $(VM_DIR)

clean :
	make -C $(ASM_DIR) clean
	make -C $(VM_DIR) clean

fclean :
	make -C $(ASM_DIR) fclean
	make -C $(VM_DIR) fclean

re:
	make fclean
	make all

testnorm :
	@/usr/bin/norminette $(shell find . -name "*.[ch]")

.PHONY: all clean fclean re
