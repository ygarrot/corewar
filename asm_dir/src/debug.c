/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:32:17 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/28 17:55:28 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_line(t_line *lines)
{
	int i;

	ft_printf("size: %d\n", lines->size);
	if (lines->label)
		ft_printf("label: (%s) ||  ", lines->label);
	ft_printf("op: (%s), params:", lines->op);
	i = -1;
	while (lines->params[++i])
		ft_printf("(%s) T(%d)  ", lines->params[i], lines->type_params[i]);
	ft_printf("\n");
}

void		print_lines(t_line *lines)
{
	while (lines)
	{
		print_line(lines);
		lines = lines->next;
	}
}

void		print_hash(t_list *hash_array[MEM_SIZE])
{
	int		i;
	t_list	*list;

	i = -1;
	while (++i < MEM_SIZE)
	{
		list = hash_array[i];
		while (list)
		{
			ft_printf("(%d) %s\n", i, (char*)list->content);
			list = list->next;
		}
	}
}
