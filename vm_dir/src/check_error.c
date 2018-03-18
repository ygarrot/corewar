/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:02:56 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/09 15:56:22 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	err_malloc(t_vm *vm, void *param)
{
	if (param == NULL)
	{
		ft_putendl_fd("Fail to malloc memory\n", 2);
		erase_vm(vm);
		exit(EXIT_FAILURE);
	}
}

int		check_reg(int tab[3][MAX_ARGS_NUMBER], int i)
{
	if (tab[T][i] == REG_CODE && tab[P][i] > 0 && tab[P][i] < REG_NUMBER + 1)
		return (1);
	return (0);
}

/*
** uniquement du check pour print
*/

int		valide_op(t_instr *instr)
{
	if (instr->opcode > 16 || instr->opcode < 1)
		return (0);
	return (1);
}

int		valide_instr(t_instr *instr)
{
	int param;
	int i;

	i = -1;
	if (instr->opcode > 16 || instr->opcode < 1)
	{
		instr->w_infos = 1;
		return (0);
	}
	while (++i < g_op[instr->opcode - 1].nb_param)
	{
		instr->params[T][i] == IND_CODE ? (param = T_IND) :
			(param = instr->params[T][i]);
		if (!(param & g_op[instr->opcode - 1].type_param[i]))
		{
			instr->w_infos = 1;
			return (0);
		}
		if (param == REG_CODE && !check_reg(instr->params, i))
		{
			instr->w_infos = 1;
			return (0);
		}
	}
	return (1);
}

void	print_pc_advance(t_vm *vm, t_process *process)
{
	int i;
	int adv;

	i = -1;
	if (process->instr->opcode == 9 && !process->instr->w_infos)
		return ;
	adv = process->next_pc % MEM_SIZE - process->pc;
	if (process->next_pc % MEM_SIZE < process->pc)
		adv = process->next_pc - process->pc;
	if (adv < 0)
		adv += MEM_SIZE;
	if (adv > 0 && adv <= 10)
	{
		ft_printf("ADV %d (%#.4x -> %#.4x) ", adv, process->pc,
				process->pc + adv);
		while (++i < adv)
			ft_printf("%.2x ", vm->map[(process->pc + i) % MEM_SIZE]);
		ft_printf("\n");
	}
}
