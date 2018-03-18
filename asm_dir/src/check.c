/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:44:20 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/18 09:53:43 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	void	check_loop(t_env *env, t_line *line, int nb, int index)
{
	int		arg;

	arg = line->type_params[nb];
	if (!arg)
		kill(env, "Syntax error", line->nb_line);
	if (arg == T_LAB)
	{
		arg = find_label_type(line->params[nb]);
		if ((search_hash(env->hash_array, line->params[nb])) == -1)
			kill(env, "Unknow label", line->nb_line);
	}
	if (!(g_op[index].type_param[nb] & arg))
		kill(env, "Invalid argument for this opcode", line->nb_line);
	if (line->type_params[nb] == T_REG &&
	param_to_hex(env, line->params[nb]) < 0)
		kill(env, "Wrong register number", line->nb_line);
}

void			check_header(t_env *env)
{
	if (!ft_strcmp(env->header->prog_name, ""))
		kill(env, "No program name", 0);
	if (ft_strstr(env->header->prog_name, ".comment"))
		kill(env, "Error on program name", 0);
	if (!env->comment)
		kill(env, "No program comment", 0);
	if (env->count > CHAMP_MAX_SIZE)
		kill(env, "Champion too big!", 0);
	if (!env->list_lines)
		kill(env, "No code in champion", 0);
}

void			check_params(t_env *env)
{
	t_line	*line;
	int		index;
	int		nb;

	line = env->list_lines;
	while (line)
	{
		if (line->op)
		{
			index = i_tab(line->op);
			if (index == 16)
				kill(env, "Invalid opcode", line->nb_line);
			nb = -1;
			while (line->params[++nb])
				check_loop(env, line, nb, index);
		}
		line = line->next;
	}
}

int				check_name(char *str)
{
	int i;

	i = ft_strlen(str);
	if (i <= 2 || str[i - 1] != 's' || str[i - 2] != '.')
		return (0);
	return (1);
}

void			check_line(t_env *env, t_line *line)
{
	int nb_param;

	if (!line)
		return ;
	nb_param = -1;
	while (nb_param < 4 && line->params[++nb_param])
		;
	if (line->label && !is_label(line->label))
		kill(env, "Invalid char in label", line->nb_line);
	if (line->label && !line->op && !nb_param)
		return ;
	if (!line->op || i_tab(line->op) == 16)
		kill(env, "Missing and/or invalid opcode", line->nb_line);
	if (g_op[i_tab(line->op)].nb_param != nb_param)
		kill(env, "Wrong number of parameters", line->nb_line);
}
