/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:46:13 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/09 18:00:52 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*my_trim(char *str)
{
	if (!str)
		return (NULL);
	while (*str && (*str == '\t' || *str == ' '))
		str++;
	return (str);
}

/*
** ajoute un nouveau param au tableau
*/

void			add_param(t_env *env, t_line *new_line, char *word, int code)
{
	int		i;

	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		if (new_line->params[i] == NULL)
		{
			if (code && i + 1 < g_op[i_tab(new_line->op)].nb_param)
			{
				if (ft_count_char(word, SEPARATOR_CHAR) != 1)
					kill(env, "Separator char missing", new_line->nb_line);
				ft_strreplace(word, SEPARATOR_CHAR, '\0');
			}
			else if (i + 1 == g_op[i_tab(new_line->op)].nb_param &&
			ft_count_char(word, SEPARATOR_CHAR) != 0)
				kill(env, "Separator char at end of", new_line->nb_line);
			new_line->params[i] = word;
			new_line->type_params[i] = find_param_type(word);
			break ;
		}
	}
}
