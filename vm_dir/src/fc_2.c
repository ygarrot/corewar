/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:12:25 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/06 10:14:22 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_add(t_vm *vm, t_instr *i, t_process *p)
{
	if (!check_reg(i->params, 0) || !check_reg(i->params, 1)
			|| !check_reg(i->params, 2))
		return ;
	p->regs[i->params[P][2] - 1] = p->regs[i->params[P][0] - 1]
		+ p->regs[i->params[P][1] - 1];
	p->carry = !p->regs[i->params[P][2] - 1];
	(vm->print & 4) ? ft_printf(" r%d r%d r%d\n", i->params[P][0],
			i->params[P][1], i->params[P][2]) : 0;
}

void	ft_sub(t_vm *vm, t_instr *i, t_process *p)
{
	if (!check_reg(i->params, 0) || !check_reg(i->params, 1)
			|| !check_reg(i->params, 2))
		return ;
	p->regs[i->params[P][2] - 1] = p->regs[i->params[P][0] - 1]
		- p->regs[i->params[P][1] - 1];
	p->carry = !p->regs[i->params[P][2] - 1];
	(vm->print & 4) ? ft_printf(" r%d r%d r%d\n", i->params[P][0],
			i->params[P][1], i->params[P][2]) : 0;
}

void	ft_and(t_vm *vm, t_instr *i, t_process *p)
{
	int a;
	int b;

	if (!check_reg(i->params, 2))
		return ;
	a = get_param_value(vm, p, 0);
	b = get_param_value(vm, p, 1);
	if (i->w_infos)
		return ;
	p->regs[i->params[P][2] - 1] = a & b;
	p->carry = !p->regs[i->params[P][2] - 1];
	(vm->print & 4) ? ft_printf(" %d %d r%d\n", a, b, i->params[P][2]) : 0;
}

void	ft_or(t_vm *vm, t_instr *i, t_process *p)
{
	int a;
	int b;

	if (!check_reg(i->params, 2))
		return ;
	a = get_param_value(vm, p, 0);
	b = get_param_value(vm, p, 1);
	if (i->w_infos)
		return ;
	p->regs[i->params[P][2] - 1] = a | b;
	p->carry = !p->regs[i->params[P][2] - 1];
	(vm->print & 4) ? ft_printf(" %d %d r%d\n", a, b, i->params[P][2]) : 0;
}

void	ft_xor(t_vm *vm, t_instr *i, t_process *p)
{
	int a;
	int b;

	if (!check_reg(i->params, 2))
		return ;
	a = get_param_value(vm, p, 0);
	b = get_param_value(vm, p, 1);
	if (i->w_infos)
		return ;
	p->regs[i->params[P][2] - 1] = a ^ b;
	p->carry = !p->regs[i->params[P][2] - 1];
	(vm->print & 4) ? ft_printf(" %d %d r%d\n", a, b, i->params[P][2]) : 0;
}
