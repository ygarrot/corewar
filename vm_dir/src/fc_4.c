/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:16:29 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/10 10:08:16 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_lldi(t_vm *vm, t_instr *i, t_process *p)
{
	int a;
	int b;
	int addr;

	if (!check_reg(i->params, 2))
		return ;
	a = get_param_value(vm, p, 0);
	b = get_param_value(vm, p, 1);
	addr = p->pc + a + b;
	if (i->w_infos)
		return ;
	p->regs[i->params[P][2] - 1] = get_nb_from_map(vm->map, addr, REG_SIZE);
	p->carry = !p->regs[i->params[P][2] - 1];
	ft_printf(" %d %d r%d\n", a, b, i->params[P][2]);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
		a, b, a + b, p->pc + a + b);
}

void		ft_lfork(t_vm *vm, t_instr *i, t_process *p)
{
	if (vm->print & 4)
		ft_printf(" %d (%d)\n", i->params[P][0], p->pc + (i->params[P][0]));
	process_dup(vm, p, get_lim((p->pc + i->params[P][0])));
}

void		ft_aff(t_vm *vm, t_instr *i, t_process *p)
{
	(void)vm;
	if (!check_reg(i->params, 0))
		return ;
	if (vm->print)
		ft_printf("Aff: %c\n", (p->regs[i->params[P][0] - 1] % 256));
}

void		ft_pass(t_vm *vm, t_instr *i, t_process *p)
{
	(void)vm;
	(void)i;
	(void)p;
	return ;
}
