/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:37 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:45:08 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *prec;
	t_list *first;

	first = NULL;
	prec = NULL;
	while (lst)
	{
		new = (f)(ft_lstnew(lst->content, lst->content_size));
		if (prec != NULL)
			prec->next = new;
		else
			first = new;
		prec = new;
		lst = lst->next;
	}
	return (first);
}
