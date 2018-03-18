/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:57:29 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:50:27 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			first_char_is_com(char *str)
{
	if (!str)
		return (0);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == COMMENT_CHAR || *str == COMMENT_CHAR2)
		return (1);
	return (0);
}

int			is_label(char *word)
{
	int j;

	j = -1;
	while (word[++j])
	{
		if (!ft_parse_char(word[j], LABEL_CHARS))
			return (0);
	}
	return (1);
}

void		del_label(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

void		free_hash(t_list **hash_array)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (hash_array[i])
			ft_lstdel(&hash_array[i], &del_label);
	}
}
