/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:38 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/13 09:43:12 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_swap(void **ptr1, void **ptr2)
{
	void	*tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static int		ft_list_size(t_list *begin_list)
{
	int		i;

	i = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}

void			ft_lst_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*list;
	int		i;
	int		size;

	i = 0;
	size = ft_list_size(*begin_list);
	list = *begin_list;
	while (i < size)
	{
		list = *begin_list;
		while (list->next)
		{
			if ((*cmp)(list->content, list->next->content) > 0)
				ft_swap(&(list->content), &(list->next->content));
			list = list->next;
		}
		i++;
	}
}
