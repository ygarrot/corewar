/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:50:47 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/06 11:02:15 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_live(t_vm *vm, t_instr *i, t_process *p)
{
	int			num;
	t_champs	*champs;

	num = -i->params[P][0];
	if ((champs = search_champs(vm, num)))
	{
		champs->last_live = vm->total_cycle;
		vm->last_alive = num;
		(vm->print & 4) ? ft_printf(" -%d\n", num) : 0;
		champs->lives++;
		if (!vm->curs.display && vm->print & 1)
			ft_printf("Player %d (%s) is said to be alive\n",
					champs->num, champs->infos.name);
		else if (!vm->curs.display && !vm->print)
			ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
					champs->num, champs->infos.name);
	}
	else if ((vm->print & 4))
		ft_printf(" %d\n", -num);
	++vm->nbr_live;
	p->live = vm->total_cycle;
	p->last_live = vm->total_cycle + 1;
}

void	ft_ld(t_vm *vm, t_instr *i, t_process *p)
{
	int addr;
	int reg_1;

	reg_1 = check_reg(i->params, 1);
	if (!reg_1 || !i->params[T][0])
		return ;
	if (i->params[T][0] == DIR_CODE)
		p->regs[i->params[P][1] - 1] = i->params[P][0];
	else if (i->params[T][0] == IND_CODE)
	{
		addr = p->pc + (i->params[P][0] % IDX_MOD);
		p->regs[i->params[P][1] - 1] = get_nb_from_map(vm->map, get_lim(addr),
				REG_SIZE);
	}
	if ((vm->print & 4))
		ft_printf(" %d r%d\n", p->regs[i->params[P][1] - 1], i->params[P][1]);
	p->carry = !p->regs[i->params[P][1] - 1];
}

void	ft_st(t_vm *vm, t_instr *i, t_process *p)
{
	if (!check_reg(i->params, 0))
		return ;
	if (check_reg(i->params, 1))
	{
		if ((vm->print & 4))
			ft_printf(" r%d %d\n", i->params[P][0], i->params[P][1]);
		p->regs[i->params[P][1] - 1] = p->regs[i->params[P][0] - 1];
	}
	else if (i->params[T][1] == IND_CODE)
	{
		if ((vm->print & 4))
			ft_printf(" r%d %d\n", i->params[P][0], i->params[P][1]);
		vm->curs.color = p->color;
		write_int_to_map(vm, get_lim(p->pc + (i->params[P][1] % IDX_MOD)),
				p->regs[i->params[P][0] - 1]);
	}
}

void	init_fc(t_vm *vm)
{
	vm->fc_tab[0] = &ft_live;
	vm->fc_tab[1] = &ft_ld;
	vm->fc_tab[2] = &ft_st;
	vm->fc_tab[3] = &ft_add;
	vm->fc_tab[4] = &ft_sub;
	vm->fc_tab[5] = &ft_and;
	vm->fc_tab[6] = &ft_or;
	vm->fc_tab[7] = &ft_xor;
	vm->fc_tab[8] = &ft_zjmp;
	vm->fc_tab[9] = &ft_ldi;
	vm->fc_tab[10] = &ft_sti;
	vm->fc_tab[11] = &ft_fork;
	vm->fc_tab[12] = &ft_lld;
	vm->fc_tab[13] = &ft_lldi;
	vm->fc_tab[14] = &ft_lfork;
	vm->fc_tab[15] = &ft_aff;
	vm->fc_tab[16] = &ft_pass;
}
