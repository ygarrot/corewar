/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:30:53 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 11:31:50 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reverse_tab(int *tab, int size)
{
	int tmp;
	int i;

	i = 0;
	while (i < size / 2)
	{
		tmp = tab[size - 1 - i];
		tab[size - i - 1] = tab[i];
		tab[i] = tmp;
		i++;
	}
}
