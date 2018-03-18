/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 11:05:35 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/01 15:46:02 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		manage_neg(int ret, int size)
{
	int i;

	i = 3;
	while ((i + 1) != size)
		ret += 0xff << (i-- * 8);
	return (ret);
}

int		is_opc(t_instr *instr)
{
	if (instr->opcode == 1 || instr->opcode == 12 || instr->opcode == 15
			|| instr->opcode == 9)
	{
		instr->params[S][0] = g_op[instr->opcode - 1].oct ? 2 : 4;
		instr->params[T][0] = DIR_CODE;
		return (1);
	}
	return (0);
}

void	fetch_instr2(t_vm *vm, t_process *process)
{
	t_instr	*instr;
	char	*byte;
	int		i;

	i = -1;
	byte = NULL;
	instr = process->instr;
	if (!is_opc(instr))
	{
		byte = convert_to_binary(vm, vm->map[get_lim(process->next_pc++)]);
		decode_byte(instr, byte);
	}
	while (++i < (g_op[instr->opcode - 1].nb_param))
	{
		instr->params[P][i] = get_nb_from_map(vm->map, process->next_pc,
				instr->params[S][i]);
		if (instr->params[S][i] == 2 && (instr->params[P][i] >> 15))
			instr->params[P][i] = manage_neg(instr->params[P][i],
					instr->params[S][i]);
		process->next_pc += instr->params[S][i];
	}
	process->next_pc = get_lim(process->next_pc);
	free(byte);
}

void	fetch_instr(t_vm *vm, t_process *process)
{
	t_instr *instr;

	instr = process->instr;
	vm->curs.color = process->color;
	vm->curs.display ? display_current(vm, process->pc, -process->next_pc) : 0;
	process->pc = get_lim(process->next_pc);
	instr->opcode = vm->map[get_lim(process->next_pc++)];
	if (instr->opcode < 1 || instr->opcode > 16)
		instr->opcode = 17;
	instr->cycle = g_op[instr->opcode - 1].nb_cycle - 1;
	process->next_pc = get_lim(process->next_pc);
}
