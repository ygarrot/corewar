/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 13:51:00 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/09 17:59:48 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			get_lim(int temp)
{
	if (temp < 0)
		temp = MEM_SIZE + (temp % MEM_SIZE);
	return (temp % MEM_SIZE);
}

void		execute_process(t_vm *vm)
{
	t_process	*process;

	process = vm->process;
	while (process)
	{
		if (!process->instr->cycle)
		{
			fetch_instr2(vm, process);
			if ((vm->print & 4) &&
				valide_instr(process->instr) && process->instr->opcode != 16)
				ft_printf("P %4d | %s", process->number,
						g_op[process->instr->opcode - 1].name);
			if (valide_instr(process->instr))
				vm->fc_tab[process->instr->opcode - 1](vm, process->instr,
						process);
			if ((vm->print & 16) && valide_op(process->instr))
				print_pc_advance(vm, process);
			process->instr->w_infos = 0;
		}
		else if (process->instr->cycle < 0)
			fetch_instr(vm, process);
		process->instr->cycle--;
		process = process->next;
	}
}

t_champs	*search_champs(t_vm *vm, int num)
{
	t_champs*temp;

	temp = vm->champs;
	while (temp && (temp->num != num))
		temp = temp->next;
	return (temp);
}

void		process_dup(t_vm *vm, t_process *p, int new_pc)
{
	t_process	*new_process;
	int			i;

	i = -1;
	err_malloc(vm, new_process = (t_process*)malloc(sizeof(t_process)));
	err_malloc(vm, new_process->instr = (t_instr*)malloc(sizeof(t_instr)));
	new_process->next_pc = new_pc;
	new_process->live = p->live;
	new_process->last_live = p->last_live;
	new_process->carry = p->carry;
	new_process->color = p->color;
	new_process->number = ++vm->total_process;
	new_process->instr->cycle = -1;
	vm->nb_process++;
	while (++i < REG_NUMBER)
		new_process->regs[i] = p->regs[i];
	new_process->instr->cycle = -1;
	new_process->next = vm->process;
	vm->process = new_process;
}
