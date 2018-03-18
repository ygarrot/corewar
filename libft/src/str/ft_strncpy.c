/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:47 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/28 18:31:18 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t j;

	j = 0;
	while (src[j] && j < n)
	{
		dest[j] = src[j];
		j++;
	}
	while (j < n)
	{
		dest[j] = '\0';
		j++;
	}
	return (dest);
}

char	*my_strncpy(const char *src, size_t n)
{
	char	*new;
	size_t	i;

	i = -1;
	if (!src || !n)
		return (NULL);
	mallcheck(new = (char*)malloc(sizeof(char) * n + 1));
	while (src[++i] && i < n)
		new[i] = src[i];
	new[i] = '\0';
	return (new);
}
