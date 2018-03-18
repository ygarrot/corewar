/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:41:30 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/26 08:28:21 by jpriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			i_tab(char *str)
{
	int i;

	if (!str)
		return (16);
	i = -1;
	while (++i < 16)
	{
		if (!ft_strcmp(str, g_op[i].name))
			return (g_op[i].opcode - 1);
	}
	return (16);
}

/*
** retourn le type du parametre
*/

int			find_param_type(char *param)
{
	if (!param)
		return (0);
	if (param[0] == 'r' && ft_isnumeric(param + 1))
		return (T_REG);
	else if (ft_isnumeric(param))
		return (T_IND);
	else if (param[0] == DIRECT_CHAR)
	{
		if (ft_strlen(param) >= 2 && param[1] == LABEL_CHAR)
			return (T_LAB);
		if (ft_strlen(param) >= 2 && ft_isnumeric(param + 1))
			return (T_DIR);
	}
	else if (param[0] == LABEL_CHAR)
		return (T_LAB);
	return (0);
}

int			find_label_type(char *label)
{
	if (!label)
		return (0);
	if (ft_strlen(label) > 2 && label[0] == '%' && label[1] == ':')
		return (T_DIR);
	else if (ft_strlen(label) > 1 && label[0] == ':')
		return (T_IND);
	return (0);
}

/*
** convertit le char de la fonction en dessous en int
*/

int			convert_binary_to_int(char *tmp)
{
	int ret;
	int i;

	ret = 0;
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] == '1')
			ret += ft_recursive_power(2, 7 - i);
	}
	return (ret);
}

/*
** return l'int correspond du param. ex : r13 return 13
*/

int			param_to_hex(t_env *env, char *param)
{
	int ret;
	int lab;

	ret = find_param_type(param);
	if (ret == T_REG)
		return (ft_atoi(param + 1));
	if (ret == T_LAB)
	{
		lab = search_hash(env->hash_array, param);
		return (lab - env->count);
	}
	if (ret == T_DIR)
		return (ft_atoi(param + 1));
	if (ret == T_IND)
		return (ft_atoi(param));
	return (0);
}
