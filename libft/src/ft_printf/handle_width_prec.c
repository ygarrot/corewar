/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_width_prec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/29 11:48:57 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** gere la largeur, ajoute 0 ou ' ' a gauche ou a droite
*/

void	handle_width(t_arg *arg)
{
	int		len;

	len = ft_strlen(arg->str);
	if (arg->width > len)
	{
		if (arg->minus)
		{
			add_str(&(arg->str), arg->zero > 0 ? '0' : ' ',
			arg->width - len, 0);
		}
		else
		{
			add_str(&(arg->str), arg->zero > 0 ? '0' : ' ',
			arg->width - len, 1);
		}
	}
}

/*
** gere la precision : cut si variable str et prec <, ajoute des 0 si >
*/

void	handle_prec(t_arg *arg)
{
	char *str;

	if (arg->var_type == STR)
	{
		if (arg->prec < (int)ft_strlen(arg->str) && arg->prec > 0)
		{
			str = ft_strsub(arg->str, 0, arg->prec);
			free(arg->str);
			arg->str = str;
		}
	}
	else if (arg->prec >= (int)ft_strlen(arg->str))
	{
		if (arg->str[0] == '+' || arg->str[0] == '-')
			add_str(&(arg->str), '0', arg->prec - ft_strlen(arg->str) + 1, 1);
		else
			add_str(&(arg->str), '0', arg->prec - ft_strlen(arg->str), 1);
	}
	if (arg->prec < 0 && arg->str[0] == '0')
		ft_strclr(arg->str);
}
