/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:39 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:37:06 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char *tmp;

	mallcheck(tmp = (char*)malloc(sizeof(char) * n));
	ft_memcpy(tmp, src, n);
	ft_memcpy(dest, tmp, n);
	free(tmp);
	return (dest);
}
