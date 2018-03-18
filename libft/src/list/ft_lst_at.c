/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:29:42 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 11:30:23 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_at(t_list *begin_list, unsigned int nbr)
{
	unsigned int i;

	i = 0;
	if (!begin_list)
		return (0);
	while (begin_list && i < nbr)
	{
		begin_list = begin_list->next;
		i++;
	}
	if (i > nbr)
		return (0);
	return (begin_list);
}
