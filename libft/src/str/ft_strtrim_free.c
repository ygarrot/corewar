/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:17:18 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:35:24 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static void	fill(char *str, char const *s, int j, int len)
{
	int i;

	i = -1;
	while (++i < len)
		str[i] = s[j++];
	str[i] = '\0';
}

char		*ft_strtrim_free(char *s)
{
	char	*str;
	int		i;
	int		len;
	int		j;

	if (!s)
		return (NULL);
	i = -1;
	while (is_space(s[++i]))
		;
	j = i;
	len = 0;
	while (s[i++])
		len++;
	i--;
	while (is_space(s[--i]))
		len--;
	if (len < 0)
		len = 0;
	mallcheck(str = (char*)malloc(len + 1));
	fill(str, s, j, len);
	free(s);
	return (str);
}
