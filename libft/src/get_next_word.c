/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:24:41 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/16 17:45:24 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_issep(char c, char *sep)
{
	while (*sep)
	{
		if (*sep == c)
			return (1);
		sep++;
	}
	return (0);
}

static int			size_word(char **line, char *sep)
{
	int i;

	i = 0;
	while ((*line)[i] && ft_issep((*line)[i], sep))
		(*line)++;
	while ((*line)[i] && !ft_issep((*line)[i], sep))
		i++;
	return (i);
}

char				*get_next_word(char **line, char *sep)
{
	int		size;
	char	*str;
	int		i;

	if (!line || !*line)
		return (NULL);
	size = size_word(line, sep);
	if (!size)
		return (NULL);
	str = ft_strnew(size);
	i = 0;
	while (**line && !ft_issep(**line, sep))
	{
		str[i++] = **line;
		(*line)++;
	}
	return (str);
}
