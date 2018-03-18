/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:46 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/07 09:34:09 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		get_flag(char c, t_arg *arg)
{
	if (c == '#')
		arg->sharp = 1;
	else if (c == '0')
		arg->zero = 1;
	else if (c == ' ')
		arg->space = 1;
	else if (c == '+')
		arg->plus = 1;
	else if (c == '-')
		arg->minus = 1;
}

static void		get_prec_and_width(char **copy, t_arg *arg, va_list ap)
{
	if (**copy == '.')
	{
		(*copy)++;
		if (**copy == '*')
		{
			get_with_star(ap, arg, STAR_PREC);
			(*copy)++;
			analyse(copy, arg, ap);
			return ;
		}
		arg->prec = ft_atoi(*copy);
		if (arg->prec == 0)
			arg->prec = -1;
	}
	else
		arg->width = ft_atoi(*copy);
	while (ft_isdigit(**copy))
		(*copy)++;
	analyse(copy, arg, ap);
}

static void		get_lenght(char **copy, t_arg *arg, va_list ap)
{
	if (**copy == 'h' && *(*copy + 1) == 'h' && arg->lenght < hh)
	{
		arg->lenght = hh;
		(*copy)++;
	}
	else if (**copy == 'l' && *(*copy + 1) == 'l' && arg->lenght < ll)
	{
		arg->lenght = ll;
		(*copy)++;
	}
	else if (**copy == 'z' && arg->lenght < z)
		arg->lenght = z;
	else if (**copy == 'l' && arg->lenght < l)
		arg->lenght = l;
	else if (**copy == 'j' && arg->lenght < j)
		arg->lenght = j;
	else if (**copy == 'h' && arg->lenght < h)
		arg->lenght = h;
	(*copy)++;
	analyse(copy, arg, ap);
}

/*
**recup les valeurs de prec et width avoir "*"
*/

void			get_with_star(va_list ap, t_arg *arg, int code)
{
	int ret;

	ret = va_arg(ap, int);
	if (code == STAR_PREC)
	{
		if (!ret)
			arg->prec = -1;
		else if (ret < 0)
			arg->prec = 0;
		else
			arg->prec = ret;
		return ;
	}
	else if (code == STAR_WIDTH)
	{
		if (ret < 0)
		{
			arg->minus = 1;
			ret = -ret;
		}
		arg->width = ret;
	}
}

/*
** Parse l argument pour check les flags
*/

void			analyse(char **copy, t_arg *arg, va_list ap)
{
	if (ft_ischarset(**copy, "bdDioOxXcCuUpsS%ZR"))
		arg->type = **copy;
	else if (ft_ischarset(**copy, "#0 +-"))
	{
		get_flag(**copy, arg);
		(*copy)++;
		analyse(copy, arg, ap);
	}
	else if (**copy == '.' || ft_isdigit(**copy))
		get_prec_and_width(copy, arg, ap);
	else if (ft_ischarset(**copy, "hjzl"))
		get_lenght(copy, arg, ap);
	else if (**copy == '*')
	{
		get_with_star(ap, arg, STAR_WIDTH);
		(*copy)++;
		analyse(copy, arg, ap);
	}
}
