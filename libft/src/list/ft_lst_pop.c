/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:37 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/02 07:57:38 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_pop(t_list **b_list)
{
	t_list *ret;

	if (!b_list || !*b_list)
		return (NULL);
	ret = *b_list;
	*b_list = (*b_list)->next;
	ret->next = NULL;
	return (ret);
}
