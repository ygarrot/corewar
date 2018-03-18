/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:47 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:52:26 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	char	*save_dest;
	size_t	i;

	i = 0;
	save_dest = dest;
	while (*dest)
		dest++;
	while (*src && i < nb)
	{
		*dest = *src;
		src++;
		dest++;
		i++;
	}
	*dest = '\0';
	return (save_dest);
}
