/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 09:49:24 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/27 14:07:06 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_merge_lists(t_list *a, t_list *b, int (*cmp)())
{
	t_list *merged_list;

	merged_list = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if ((cmp)(a->content, b->content) <= 0)
	{
		merged_list = a;
		merged_list->next = ft_merge_lists(a->next, b, cmp);
	}
	else
	{
		merged_list = b;
		merged_list->next = ft_merge_lists(a, b->next, cmp);
	}
	return (merged_list);
}

void	split_list(t_list *head, t_list **front, t_list **back)
{
	t_list *fast;
	t_list *slow;

	if (!head || !head->next)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

void	ft_merge_sort(t_list **begin_list, int (*cmp)())
{
	t_list *head;
	t_list *a;
	t_list *b;

	head = *begin_list;
	a = NULL;
	b = NULL;
	if (!head || !head->next)
		return ;
	split_list(head, &a, &b);
	ft_merge_sort(&a, cmp);
	ft_merge_sort(&b, cmp);
	*begin_list = ft_merge_lists(a, b, cmp);
}
