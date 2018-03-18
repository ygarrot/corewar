/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:38 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:45:14 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cs;

	i = -1;
	cs = (unsigned char*)s;
	while (++i < n)
	{
		if (cs[i] == (unsigned char)c)
			return ((void*)&(cs[i]));
	}
	return (NULL);
}
