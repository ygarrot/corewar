/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:00:16 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/05 12:32:11 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vm		*init_vm(void)
{
	t_vm	*vm;

	if (!(vm = (t_vm*)ft_memalloc(sizeof(t_vm))))
		return (NULL);
	vm->dump = -1;
	return (vm);
}

t_process	*init_process(t_vm *vm)
{
	t_process	*process;

	err_malloc(vm, process = (t_process*)ft_memalloc(sizeof(t_process)));
	err_malloc(vm, process->instr = (t_instr*)ft_memalloc(sizeof(t_instr)));
	ft_bzero(process->regs, sizeof(process->regs));
	return (process);
}

void		add_champs(t_vm *vm, int num)
{
	t_champs	*toadd;
	t_champs	*temp;

	err_malloc(vm, toadd = (t_champs*)ft_memalloc(sizeof(t_champs)));
	toadd->num = num;
	toadd->color = vm->players;
	if (!vm->champs)
	{
		vm->champs = toadd;
		return ;
	}
	temp = vm->champs;
	while (temp->next && (temp->next->num != toadd->num || !toadd->num))
		temp = temp->next;
	if (vm->champs->num && (vm->champs->num == num || temp->next))
		exit_parsing(vm, "Player number is already taken\n", NULL);
	temp->next = toadd;
}
