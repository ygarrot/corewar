/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:38 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:45:12 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	int				ok;
	unsigned char	*cpyd;
	unsigned char	*cpys;

	i = -1;
	ok = 0;
	cpyd = (unsigned char*)dest;
	cpys = (unsigned char*)src;
	while (++i < n)
	{
		cpyd[i] = cpys[i];
		if (cpys[i] == (unsigned char)c)
		{
			ok = 1;
			break ;
		}
	}
	if (ok)
		return (&(cpyd[i + 1]));
	return (NULL);
}
