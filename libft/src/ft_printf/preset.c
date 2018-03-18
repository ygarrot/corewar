/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/07 09:14:23 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** gere les cas de flags incompatibles
*/

void	conflict(t_arg *arg)
{
	if (arg->minus && arg->zero)
		arg->zero = 0;
	if (arg->plus && arg->space)
		arg->space = 0;
	if (arg->type == 'p')
		arg->sharp = 1;
	if (arg->type == 'p' && arg->space)
		arg->space = 0;
	if (arg->type == 'p' && arg->plus)
		arg->plus = 0;
	if (arg->prec != 0 && (arg->var_type == INT || arg->var_type == U_INT))
		arg->zero = 0;
	if (arg->prec > (int)ft_strlen(arg->str))
		arg->space = 0;
}

/*
** gere C S D O U
*/

void	handle_lenght(t_arg *arg)
{
	if (arg->type == 'c' && arg->lenght == l)
		arg->type = 'C';
	if (arg->type == 's' && arg->lenght == l)
		arg->type = 'S';
	if (arg->type == 'U')
	{
		arg->lenght = l;
		arg->type = 'u';
	}
	if (arg->type == 'D')
	{
		arg->lenght = l;
		arg->type = 'd';
	}
	if (arg->type == 'O')
	{
		arg->lenght = l;
		arg->type = 'o';
	}
}

/*
** recupere le type de la variable
*/

void	get_vartype(t_arg *arg)
{
	handle_lenght(arg);
	if (arg->type == 'd' || arg->type == 'i' || arg->type == 'b')
		arg->var_type = INT;
	else if (arg->type == 'u' || arg->type == 'p' || arg->type == 'o'
	|| arg->type == 'x' || arg->type == 'X')
		arg->var_type = U_INT;
	else if (arg->type == 's' || arg->type == 'S')
		arg->var_type = STR;
	else if (arg->type == 'c' || arg->type == 'C')
		arg->var_type = CHAR;
}
