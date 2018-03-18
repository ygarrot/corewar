/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 13:24:45 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/09 18:05:40 by mvigne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_queue(t_vm *vm)
{
	int			i;
	t_process	*temp;

	i = -1;
	(vm->print && vm->curs.display) ? vm->print = 0 : 0;
	err_malloc(vm, vm->map = (unsigned char*)ft_strnew(MEM_SIZE));
	ft_bzero(vm->curs.color_map, sizeof(vm->curs.color_map));
	vm->process = init_process(vm);
	temp = vm->process;
	temp->number = vm->players;
	while (++i < (vm->players - 1))
	{
		err_malloc(vm, temp->next = init_process(vm));
		temp->next->number = vm->players - i - 1;
		temp = temp->next;
	}
	vm->nb_process = vm->players;
	vm->total_process = vm->nb_process;
	init_fc(vm);
}

void	set_process(t_vm *vm, int index, int pc, t_champs *champs)
{
	t_process	*process;

	process = vm->process;
	if (!champs->num)
	{
		while (search_champs(vm, vm->cycle))
			vm->cycle++;
		champs->num = vm->cycle;
		vm->cycle++;
	}
	while (--index)
		process = process->next;
	process->color = champs->color;
	process->regs[0] = -champs->num;
	process->next_pc = pc;
	process->instr->cycle = -1;
}

void	set_display(t_vm *vm, t_champs *champs, int start)
{
	int i;

	i = -1;
	while (++i < champs->infos.size)
		vm->curs.color_map[start + i] = champs->num;
}

void	set_arena(t_vm *vm)
{
	int			div;
	t_champs	*champs;
	int			i;
	int			head_size;

	i = 0;
	head_size = PROG_NAME_LENGTH + COMMENT_LENGTH + 4 + 4 + 8;
	div = 0;
	init_queue(vm);
	champs = vm->champs;
	vm->total_process = vm->nb_process;
	while (champs)
	{
		if (div + champs->infos.size < MEM_SIZE)
			ft_memcpy(&vm->map[div], &champs->infos.file[head_size],
					champs->infos.size);
		else
			exit_parsing(vm, "The arena is too small\n", NULL);
		set_process(vm, vm->players - i, div, champs);
		set_display(vm, champs, div);
		div += (MEM_SIZE / vm->players);
		champs = champs->next;
		i++;
	}
	vm->curs.display ? init_ncurses(vm) : 0;
}
