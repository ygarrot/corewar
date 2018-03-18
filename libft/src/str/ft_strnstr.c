/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:48 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:52:49 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t i_to_find;

	i = 0;
	i_to_find = 0;
	if (*to_find == '\0')
		return ((char*)str);
	while (str[i] && i < len)
	{
		if (to_find[i_to_find] == str[i])
		{
			while (to_find[i_to_find] == str[i + i_to_find] &&
			i + i_to_find < len)
			{
				i_to_find++;
				if (to_find[i_to_find] == '\0')
					return ((char*)(str + i));
			}
			i_to_find = 0;
		}
		i++;
	}
	return (0);
}
