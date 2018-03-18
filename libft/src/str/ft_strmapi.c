/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:47 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:32:28 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i])
		;
	mallcheck(str = (char*)malloc(i + 1));
	i = -1;
	while (s[++i])
		str[i] = (f)(i, s[i]);
	str[i] = s[i];
	return (str);
}
