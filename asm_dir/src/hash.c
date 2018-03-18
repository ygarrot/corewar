/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:20:09 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/09 17:48:58 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*label_name(char *label)
{
	if (*label == DIRECT_CHAR)
		label++;
	if (*label == LABEL_CHAR)
		label++;
	return (label);
}

/*
** return l'adresse memoire du label
*/

int			search_hash(t_list **hash_array, char *label)
{
	int		i;
	t_list	*list;

	label = label_name(label);
	i = -1;
	while (++i < MEM_SIZE)
	{
		list = hash_array[i];
		while (list)
		{
			if (!ft_strcmp((char*)list->content, label))
				return (i);
			list = list->next;
		}
	}
	return (-1);
}

void		add_hash(t_list **hash_array, char *label, int index)
{
	t_list	*list;

	list = hash_array[index];
	while (list)
		list = list->next;
	ft_lstadd(&hash_array[index], ft_lstnew(label, ft_strlen(label) + 1));
}

/*
** return la taille en octet du parametre
*/

int			size_param(t_line *current, char *word, int type)
{
	if (type == T_REG)
		return (1);
	if (type == T_IND)
		return (2);
	if (type == T_DIR)
		return (g_op[i_tab(current->op)].oct ? 2 : 4);
	if (type == T_LAB)
	{
		if (find_label_type(word) == T_IND)
			return (2);
		else
			return (g_op[i_tab(current->op)].oct ? 2 : 4);
	}
	return (0);
}

/*
** parcours les lignes pour trouver et stoquer l'adresse des labels
*/

void		construct_hash_label(t_env *env)
{
	t_line	*current;
	int		i;

	current = env->list_lines;
	while (current)
	{
		if (current->label && !current->op)
		{
			add_hash(env->hash_array, label_name(current->label), env->count);
			current = current->next;
			continue ;
		}
		else if (current->label)
			add_hash(env->hash_array, label_name(current->label), env->count);
		current->size += g_op[i_tab(current->op)].instr ? 2 : 1;
		i = -1;
		while (current->params[++i])
			current->size += size_param(current, current->params[i],
			current->type_params[i]);
		env->count += current->size;
		current = current->next;
	}
}
