/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:33:00 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/09 13:00:38 by mvigne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	check_1st_process(t_vm *vm)
{
	t_process	*to_check;
	t_champs	*champs;

	champs = vm->champs;
	champs->lives = 0;
	while ((champs = champs->next))
		champs->lives = 0;
	if (!vm->process)
		return ;
	to_check = vm->process;
	while (to_check && !to_check->live)
	{
		vm->process = vm->process->next;
		(vm->print & 8) ? ft_printf("Process %d hasn't lived for %d cycles \
(CTD %d)\n", to_check->number, vm->total_cycle - to_check->last_live,
		vm->cycle_to_die) : 0;
		vm->curs.display ? flash() : 0;
		kill_process(&to_check);
		vm->nb_process--;
		to_check = vm->process;
	}
	to_check ? to_check->live = 0 : 0;
}

void	check_process(t_vm *vm)
{
	t_process *to_check;
	t_process *to_del;

	check_1st_process(vm);
	to_check = vm->process;
	while (to_check && to_check->next)
	{
		if (to_check->next->live)
		{
			to_check->next->live = 0;
			to_check = to_check->next;
		}
		else
		{
			vm->nb_process--;
			to_del = to_check->next;
			to_check->next = to_del->next;
			(vm->print & 4) ? ft_printf("Process %d hasn't lived for %d cycles \
(CTD %d)\n", to_del->number, vm->total_cycle -
			to_del->last_live, vm->cycle_to_die) : 0;
			kill_process(&to_del);
		}
	}
}

void	check_lives(t_vm *vm)
{
	check_process(vm);
	if (vm->nbr_live >= NBR_LIVE || vm->last_check >= MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->print & 2)
			ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
		vm->last_check = 0;
	}
	vm->nbr_live = 0;
	vm->last_check++;
	vm->cycle = 0;
}

void	running(t_vm *vm)
{
	t_process *temp;

	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle = 0;
	vm->total_cycle = 1;
	vm->dump >= 0 ? vm->dump++ : 0;
	while (vm->nb_process > 0 && vm->cycle_to_die >= 0 && --vm->dump)
	{
		(vm->cycle >= vm->cycle_to_die) ? check_lives(vm) : 0;
		if (vm->process == 0)
			break ;
		if (vm->print & 2)
			ft_printf("It is now cycle %d\n", vm->total_cycle);
		execute_process(vm);
		vm->curs.display || vm->print ? display_fc(vm) : 0;
		vm->cycle++;
		vm->total_cycle++;
	}
	vm->curs.display ? endwin() : 0;
	temp = vm->process;
	while (temp)
	{
		temp->live = 0;
		temp = temp->next;
	}
}
