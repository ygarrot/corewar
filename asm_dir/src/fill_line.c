/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 11:30:58 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/01 10:07:20 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	remove_comment(char **word)
{
	ft_strreplace(*word, COMMENT_CHAR, '\0');
	ft_strreplace(*word, COMMENT_CHAR2, '\0');
}

static void	get_params(t_env *env, t_line *new_line, char **ptr)
{
	char	*word;
	int		nb_param;

	if (!*ptr)
		return ;
	remove_comment(ptr);
	nb_param = g_op[i_tab(new_line->op)].nb_param;
	if (nb_param != 1 && ft_count_char(*ptr, SEPARATOR_CHAR) != nb_param - 1)
		kill(env, "Wrong number of separator char", new_line->nb_line);
	while ((word = get_next_word(ptr, ",")))
	{
		word = ft_strtrim_free(word);
		add_param(env, new_line, word, 0);
	}
}

static char	*find_label(char **ptr)
{
	int		i;
	char	*label;

	if (!*ptr)
		return (NULL);
	i = 0;
	*ptr = my_trim(*ptr);
	label = NULL;
	while ((*ptr)[i] && !ft_parse_char((*ptr)[i], ": \t"))
	{
		i++;
		if ((*ptr)[i] == LABEL_CHAR && !ft_strnchr(*ptr, DIRECT_CHAR, i))
		{
			label = my_strncpy(*ptr, i);
			*ptr += i + 1;
			break ;
		}
	}
	return (label);
}

static char	*find_op(char **ptr)
{
	char	*op;
	int		i;
	int		check;

	if (!*ptr)
		return (NULL);
	*ptr = my_trim(*ptr);
	op = NULL;
	i = -1;
	check = 0;
	while ((*ptr)[++i] && !ft_parse_char((*ptr)[i], ": \t"))
	{
		if ((*ptr)[i] == DIRECT_CHAR)
		{
			check = 1;
			break ;
		}
	}
	op = my_strncpy(*ptr, i);
	if (i_tab(op) == 16)
		ft_memdel((void**)&op);
	else
		*ptr += i + 1;
	check ? *ptr -= 1 : 0;
	return (op);
}

t_line		*fill_line(t_env *env, t_line *new_line, char *ptr)
{
	new_line->label = find_label(&ptr);
	if (find_label(&ptr))
		kill(env, "Syntax error", new_line->nb_line);
	new_line->op = find_op(&ptr);
	if (new_line->label && !new_line->op)
		return (new_line);
	get_params(env, new_line, &ptr);
	return (new_line);
}
