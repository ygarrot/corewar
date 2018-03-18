/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str_nb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/07 09:15:33 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**Ces fonctions recuperent le nombre et le transforme en char*,
**dans la bonne base et avec les bonnes conversions
*/

static void	get_base(char base[17], t_arg *arg)
{
	if (arg->type == 'o')
		ft_strcpy(base, "01234567");
	else if (arg->type == 'x' || arg->type == 'p')
		ft_strcpy(base, "0123456789abcdef");
	else if (arg->type == 'X')
		ft_strcpy(base, "0123456789ABCDEF");
	else if (arg->type == 'b')
		ft_strcpy(base, "01");
	else
		ft_strcpy(base, "0123456789");
}

void		get_str_nb(va_list ap, t_arg *arg)
{
	long long int	nb;
	char			base[17];

	get_base(base, arg);
	nb = va_arg(ap, long long int);
	if (arg->lenght == l)
		nb = (long)nb;
	else if (arg->lenght == ll)
		;
	else if (arg->lenght == h)
		nb = (short)nb;
	else if (arg->lenght == hh)
		nb = (char)nb;
	else if (arg->lenght == j)
		nb = (intmax_t)nb;
	else if (arg->lenght == z)
		nb = (size_t)nb;
	else
		nb = (int)nb;
	arg->str = ft_lltoa_base(nb, base);
}

void		get_str_u_nb(va_list ap, t_arg *arg)
{
	unsigned long long	nb;
	char				base[17];

	get_base(base, arg);
	nb = va_arg(ap, unsigned long long);
	if (arg->lenght == ll)
		;
	else if (arg->lenght == h)
		nb = (unsigned short)nb;
	else if (arg->lenght == hh)
		nb = (unsigned char)nb;
	else if (arg->type == 'p' || arg->lenght == l)
		nb = (unsigned long)nb;
	else if (arg->lenght == j)
		nb = (uintmax_t)nb;
	else if (arg->lenght == z)
		nb = (size_t)nb;
	else
		nb = (unsigned int)nb;
	arg->str = ft_ulltoa_base(nb, base);
}
