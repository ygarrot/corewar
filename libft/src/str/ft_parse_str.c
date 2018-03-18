/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:40 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/13 09:38:12 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_parse_str(char *str, char *charset)
{
	int i;

	while (*str)
	{
		i = 0;
		while (charset[i])
		{
			if (charset[i] == *str)
				return (1);
			i++;
		}
		str++;
	}
	return (0);
}
