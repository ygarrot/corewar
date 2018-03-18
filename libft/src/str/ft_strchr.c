/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:44 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/01 09:40:48 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char cc;

	cc = (char)c;
	while (*s)
	{
		if (*s == cc)
			return ((char*)s);
		s++;
	}
	if (cc == '\0')
		return ((char*)s);
	return (NULL);
}

char	*ft_strnchr(const char *s, int c, size_t n)
{
	char	cc;
	size_t	i;

	i = 0;
	cc = (char)c;
	while (*s && i < n)
	{
		if (*s == cc)
			return ((char*)s);
		s++;
		i++;
	}
	if (cc == '\0')
		return ((char*)s);
	return (NULL);
}
