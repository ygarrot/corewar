/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:38 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/02 07:59:18 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_reverse(t_list **begin_list)
{
	t_list *save_next;
	t_list *new;
	t_list *copy;

	if (begin_list)
	{
		new = 0;
		copy = *begin_list;
		while (copy)
		{
			save_next = copy->next;
			copy->next = new;
			new = copy;
			copy = save_next;
		}
		*begin_list = new;
	}
}
