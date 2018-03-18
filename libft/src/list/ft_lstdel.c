/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:34 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:42:41 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *save;

	if (alst == NULL || *alst == NULL)
		return ;
	while (*alst)
	{
		save = (*alst)->next;
		(del)((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = save;
	}
	*alst = NULL;
}
