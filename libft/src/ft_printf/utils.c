/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:25:17 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** supprime un certain nombre de char d une chaine et free
*/

void	str_cut_first_n_free(char **str, int nb)
{
	size_t	size;
	char	*new;
	int		i;

	if (!str)
		return ;
	size = ft_strlen(*str);
	mallcheck(new = (char*)malloc(sizeof(char) * size - nb + 1));
	if (!new)
		return ;
	i = -1;
	while (++i < nb)
		;
	ft_strcpy(new, str[i]);
	free(*str);
}

/*
** comme strjoin mais avec le free integre
*/

void	str_join_n_free(char *to_add, char **src, int type)
{
	char	*new;

	if (!to_add || !*src)
		return ;
	mallcheck(new = (char*)malloc(ft_strlen(to_add) + ft_strlen(*src) + 1));
	if (!new)
		return ;
	if (type == JOIN_START)
	{
		ft_strcpy(new, to_add);
		ft_strcat(new, *src);
	}
	if (type == JOIN_END)
	{
		ft_strcpy(new, *src);
		ft_strcat(new, to_add);
	}
	if (type == JOIN_START || type == JOIN_END)
	{
		free(*src);
		*src = new;
	}
}

/*
** fonction qui ajoute les 0 ou ' ' a une chaine
*/

void	add_str(char **str, char type, int number, int start)
{
	char	*new;
	char	*tmp;

	mallcheck(tmp = (char*)malloc(sizeof(char) * (number + 1)));
	if (!tmp)
		return ;
	ft_memset(tmp, type, number);
	tmp[number] = '\0';
	if (!start)
		new = ft_strjoin(*str, tmp);
	else
	{
		if (((*str)[0] == '-' || (*str)[0] == '+'
		|| (*str)[0] == ' ') && type == '0')
		{
			tmp[0] = (*str)[0];
			(*str)[0] = '0';
		}
		new = ft_strjoin(tmp, *str);
	}
	free(*str);
	free(tmp);
	*str = new;
}
