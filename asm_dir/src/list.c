/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:43:25 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/09 17:51:12 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		push_end_line(t_line **head, t_line *new_line)
{
	t_line	*current;

	if (!head || !new_line)
		return ;
	if (!*head)
		*head = new_line;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_line;
	}
}

void		free_lines(t_line **lines)
{
	t_line		*save;
	int			i;

	if (!lines || !*lines)
		return ;
	while (*lines)
	{
		save = (*lines)->next;
		ft_memdel((void**)&(*lines)->label);
		ft_memdel((void**)&(*lines)->op);
		i = -1;
		while (++i < 4)
			ft_memdel((void**)&(*lines)->params[i]);
		ft_memdel((void**)&(*lines)->params);
		ft_memdel((void**)&(*lines)->type_params);
		ft_memdel((void**)lines);
		*lines = save;
	}
	*lines = NULL;
}
