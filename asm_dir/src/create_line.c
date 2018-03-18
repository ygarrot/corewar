/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 11:33:30 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:44:25 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		get_label(t_env *env, t_line *new_line, char *word)
{
	int i;

	if (new_line->label)
		kill(env, "Syntax error", new_line->nb_line);
	if (ft_count_char(word, LABEL_CHAR) != 1)
		kill(env, "Syntax error in label", new_line->nb_line);
	ft_strreplace(word, LABEL_CHAR, '\0');
	i = -1;
	while (word[++i])
	{
		if (!ft_parse_char(word[i], LABEL_CHARS))
			kill(env, "Syntax error, unauthorized label char",
			new_line->nb_line);
	}
	new_line->label = word;
}

t_line		*create_line(t_env *env, char *ptr)
{
	t_line	*new_line;

	mallcheck(new_line = (t_line*)ft_memalloc(sizeof(t_line)));
	mallcheck(new_line->params = (char**)ft_memalloc(sizeof(char*)
		* MAX_ARGS_NUMBER));
	mallcheck(new_line->type_params = (int*)ft_memalloc(sizeof(int)
		* MAX_ARGS_NUMBER));
	new_line->nb_line = env->nb_line;
	new_line = fill_line(env, new_line, ptr);
	check_line(env, new_line);
	return (new_line);
}
