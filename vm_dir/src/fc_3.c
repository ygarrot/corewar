/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:14:44 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/09 15:55:01 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_zjmp(t_vm *vm, t_instr *i, t_process *p)
{
	i->w_infos = 0;
	if (p->carry)
	{
		p->next_pc = p->pc + (i->params[P][0] % IDX_MOD);
		(vm->print & 4) ? ft_printf(" %d OK\n", i->params[P][0]) : 0;
	}
	else if ((i->w_infos = 1))
		(vm->print & 4) ? ft_printf(" %d FAILED\n", i->params[P][0]) : 0;
}

void		ft_ldi(t_vm *vm, t_instr *i, t_process *p)
{
	int a;
	int b;
	int addr;

	if (!check_reg(i->params, 2))
		return ;
	a = get_param_value(vm, p, 0);
	b = get_param_value(vm, p, 1);
	if (i->w_infos)
		return ;
	addr = p->pc + ((a + b) % IDX_MOD);
	p->regs[i->params[P][2] - 1] = get_nb_from_map(vm->map, addr, REG_SIZE);
	if ((vm->print & 4))
	{
		ft_printf(" %d %d r%d\n", a, b, i->params[P][2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
				a, b, a + b, p->pc + ((a + b) % IDX_MOD));
	}
}

void		ft_sti(t_vm *vm, t_instr *i, t_process *p)
{
	int a;
	int b;

	if (!check_reg(i->params, 0))
		return ;
	a = get_param_value(vm, p, 1);
	b = get_param_value(vm, p, 2);
	if (i->w_infos)
		return ;
	if ((vm->print & 4))
	{
		ft_printf(" r%d %d %d\n", i->params[P][0], a, b);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
				a, b, a + b, p->pc + ((a + b) % IDX_MOD));
	}
	vm->curs.color = p->color;
	write_int_to_map(vm, p->pc + ((a + b) % IDX_MOD),
	p->regs[i->params[P][0] - 1]);
}

void		ft_fork(t_vm *vm, t_instr *i, t_process *p)
{
	(vm->print & 4) ? ft_printf(" %d (%d)\n", i->params[P][0], p->pc +
				(i->params[P][0] % IDX_MOD)) : 0;
	process_dup(vm, p, get_lim(p->pc + (i->params[P][0] % IDX_MOD)));
}

void		ft_lld(t_vm *vm, t_instr *i, t_process *p)
{
	if (!check_reg(i->params, 1))
		return ;
	if (i->params[T][0] == DIR_CODE)
		p->regs[i->params[P][1] - 1] = i->params[P][0];
	else if (i->params[T][0] == IND_CODE)
		p->regs[i->params[P][1] - 1] = get_nb_from_map(vm->map, p->pc +
				i->params[P][0], REG_SIZE);
	else
		return ;
	if ((vm->print & 4))
		ft_printf(" %d r%d\n", p->regs[i->params[P][1] - 1], i->params[P][1]);
	p->carry = !p->regs[i->params[P][1] - 1];
}
