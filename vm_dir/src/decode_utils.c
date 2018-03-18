/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 14:30:25 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/01 15:46:13 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_param_value(t_vm *vm, t_process *p, int i)
{
	t_instr *instr;

	instr = p->instr;
	instr->w_infos = 0;
	if (instr->params[T][i] == DIR_CODE)
		return (instr->params[P][i]);
	if (check_reg(instr->params, i))
		return (p->regs[instr->params[P][i] - 1]);
	if (p->instr->params[T][i] == IND_CODE)
	{
		return (get_nb_from_map(vm->map, p->pc + (instr->params[P][i] % IDX_MOD)
					, (instr->opcode == 10 || instr->opcode == 14) ? 2 : 4));
	}
	return (instr->w_infos = 1);
}

char	*convert_to_binary(t_vm *vm, unsigned char a)
{
	int		i;
	char	*octet;

	err_malloc(vm, octet = (char*)ft_memalloc(9 * sizeof(char)));
	i = 8;
	while (--i >= 0)
	{
		octet[i] = (a & 1) + '0';
		a >>= 1;
	}
	octet[8] = '\0';
	return (octet);
}

void	decode_byte(t_instr *instr, char *byte)
{
	int i;

	i = -1;
	ft_bzero(instr->params, sizeof(instr->params));
	while (++i < g_op[instr->opcode - 1].nb_param)
	{
		instr->params[T][i] = (*byte - '0') * 2 + (*(byte + 1) - '0');
		if (*byte == '0' && *(byte + 1) == '1')
			instr->params[S][i] = 1;
		else if (*byte == '1' && *(byte + 1) == '0')
			instr->params[S][i] = g_op[instr->opcode - 1].oct ? 2 : 4;
		else if (*byte == '1' && *(byte + 1) == '1')
			instr->params[S][i] = IND_SIZE;
		else
			instr->params[S][i] = 0;
		byte += 2;
	}
}

int		get_nb_from_map(unsigned char *map, int index, int nb_bytes)
{
	int ret;
	int i;

	ret = 0;
	i = -1;
	while (++i < nb_bytes)
		ret = (ret << 8) | map[get_lim(index + i)];
	return (ret);
}

void	write_int_to_map(t_vm *vm, int addr, int x)
{
	vm->map[get_lim(addr + 3)] = (unsigned char)(x & 0x000000FF);
	vm->map[get_lim(addr + 2)] = (unsigned char)((x & 0x0000FF00) >> 8);
	vm->map[get_lim(addr + 1)] = (unsigned char)((x & 0x00FF0000) >> 16);
	vm->map[get_lim(addr + 0)] = (unsigned char)((x & 0xff000000) >> 24);
	if (vm->curs.display)
		display_current(vm, addr, 4);
	vm->curs.color = 0;
}
