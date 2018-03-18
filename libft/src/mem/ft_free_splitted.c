/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_splitted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:58:26 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/31 13:00:00 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_splitted(char **splitted)
{
	int i;

	if (!splitted)
		return ;
	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	ft_memdel((void**)&splitted);
}
