/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:05:44 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/09 10:36:13 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	kill_process(t_process **temp)
{
	if (!*temp)
		return ;
	ft_memdel((void**)&(*temp)->instr);
	ft_memdel((void**)temp);
}

void	erase_champ(t_champs *champs)
{
	ft_memdel((void**)&champs->infos.name);
	ft_memdel((void**)&champs->infos.comment);
	ft_memdel((void**)&champs->infos.file);
	ft_memdel((void**)&champs);
}

void	erase_vm(t_vm *vm)
{
	t_champs	*to_del;
	t_process	*process_to_del;

	if (!vm)
		return ;
	while (vm->champs)
	{
		to_del = vm->champs;
		vm->champs = vm->champs->next;
		erase_champ(to_del);
	}
	while (vm->process)
	{
		process_to_del = vm->process;
		vm->process = vm->process->next;
		kill_process(&process_to_del);
	}
	ft_memdel((void**)&vm->map);
	ft_memdel((void**)&vm->curs.bas);
	ft_memdel((void**)&vm->curs.haut);
	ft_memdel((void**)&vm);
}

void	exit_parsing(t_vm *vm, char *str, char *arg)
{
	if (str)
		arg ? ft_printf(str, arg) : ft_printf(str);
	else
		ft_printf("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] [-d\
isplay] [-show N]\n\
/#### TEXT OUTPUT MODE #######################################################\
\n-show N      : Verbosity levels, can be added together to enable several\n\
	- 0 : Show only essentials\n\
	- 1 : Show lives\n\
	- 2 : Show cycles\n\
	- 4 : Show operations (Params are NOT litteral ...)\n\
	- 8 : Show deaths\n\
	- 16 : Show PC movements (Except for jumps)\n\
/#### NCURSES OUTPUT MODE ####################################################\
\n-display        : Ncurses output mode\n");
	erase_vm(vm);
	exit(0);
}
