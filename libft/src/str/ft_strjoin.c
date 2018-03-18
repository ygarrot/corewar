/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:46 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:31:52 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	mallcheck(str = (char*)malloc(ft_strlen((char*)s1)
		+ ft_strlen((char*)s2) + 1));
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	i -= 1;
	while (s2[++j])
		str[++i] = s2[j];
	str[++i] = '\0';
	return (str);
}
