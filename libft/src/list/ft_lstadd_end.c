/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:27:30 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 11:34:06 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_end(t_list **head, t_list *elem)
{
	t_list *current;

	if (!head || !elem)
		return ;
	if (!*head)
		*head = elem;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = elem;
	}
}
