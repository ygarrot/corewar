/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:36:51 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/15 14:30:44 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			create_file(char *file)
{
	char	new[ft_strlen(file) + 3];
	size_t	len;

	len = ft_strlen(file);
	ft_strncpy(new, file, len - 1);
	new[len - 1] = '\0';
	ft_strcat(new, "cor");
	ft_printf("Write output program to %s\n", new);
	return (open(new, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU));
}

/*
** Fonction qui calcule le codage des parametres
** 01 : registre
** 10 : direct
** 11 : indirect
*/

int			calc_instr_code(t_line *current)
{
	char	tmp[9];
	int		i;
	int		i_tmp;
	int		type;

	ft_memset(tmp, '0', sizeof(tmp));
	i = -1;
	i_tmp = -1;
	while (current->params[++i])
	{
		type = current->type_params[i] == T_LAB ?
			find_label_type(current->params[i]) :
			current->type_params[i];
		fill_tmp(type, tmp, &i_tmp);
	}
	tmp[8] = '\0';
	return (convert_binary_to_int(tmp));
}

void		fill_tmp(int type, char tmp[9], int *i_tmp)
{
	if (type == T_REG)
	{
		tmp[++(*i_tmp)] = '0';
		tmp[++(*i_tmp)] = '1';
	}
	else if (type == T_DIR)
	{
		tmp[++(*i_tmp)] = '1';
		tmp[++(*i_tmp)] = '0';
	}
	else if (type == T_IND)
	{
		tmp[++(*i_tmp)] = '1';
		tmp[++(*i_tmp)] = '1';
	}
}
