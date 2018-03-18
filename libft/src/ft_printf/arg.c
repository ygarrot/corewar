/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:46 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:22:50 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** envoie a la bonne fonction en fonction du type de variable
*/

void	get_str(va_list ap, t_arg *arg)
{
	char tmp[2];

	if (arg->var_type == INT)
		get_str_nb(ap, arg);
	else if (arg->var_type == U_INT)
		get_str_u_nb(ap, arg);
	else if (arg->var_type == STR)
		get_str_str(ap, arg);
	else if (arg->var_type == CHAR)
		get_str_char(ap, arg);
	if (arg->type == '%' || arg->type == 'R' || arg->type == 'Z')
	{
		tmp[0] = arg->type;
		tmp[1] = '\0';
		arg->str = ft_strdup(tmp);
	}
}

/*
** fonction spe pour decaler le flag avec les 0 devants
*/

void	switch_x(t_arg *arg)
{
	int i;

	i = -1;
	while (arg->str[++i])
	{
		if (arg->str[i] == 'x')
		{
			if (ft_strlen(arg->str) > 3)
			{
				arg->str[i] = '0';
				arg->str[1] = 'x';
			}
		}
		if (arg->str[i] != '0')
			break ;
	}
}

/*
** modifier la string selon : precision, signe, sharp, width
*/

void	modif_str(t_arg *arg)
{
	if (arg->type != 'c' && arg->type != 'C' && arg->type != '%')
		handle_prec(arg);
	if (arg->type == 'd' || arg->type == 'i' || arg->type == 'p')
		handle_sign(arg);
	handle_sharp(arg);
	handle_width(arg);
	if (arg->sharp && arg->width)
		switch_x(arg);
}

/*
** coeur de la fonction qui gere l'argument
*/

int		ft_arg(int fd, char **copy, va_list ap, int *write)
{
	t_arg *arg;

	mallcheck(arg = (t_arg*)ft_memalloc(sizeof(t_arg)));
	(*copy)++;
	analyse(copy, arg, ap);
	if (!arg->type)
	{
		free(arg);
		(*copy)--;
		return (1);
	}
	get_vartype(arg);
	get_str(ap, arg);
	conflict(arg);
	if (!arg->char_null)
		modif_str(arg);
	print_arg(fd, arg, write);
	free(arg->str);
	free(arg);
	return (1);
}
