/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:38 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:45:16 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = -1;
	while (++i < n)
	{
		if (((unsigned char*)s1)[i] != ((unsigned char*)s2)[i])
			return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
	}
	return (0);
}
