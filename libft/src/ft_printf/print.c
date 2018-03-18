/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:36:25 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/07 11:40:17 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** print l'arg, gere le cas du char 0, incremente le comteur de retour
*/

void	print_arg(int fd, t_arg *arg, int *to_write)
{
	int		i;
	char	c;

	*to_write += ft_strlen(arg->str);
	write(fd, arg->str, ft_strlen(arg->str));
	if (arg->char_null)
	{
		if (!arg->width)
			*to_write += 1;
		else
		{
			if (arg->width && !arg->minus)
			{
				c = arg->zero ? '0' : ' ';
				i = 0;
				while (++i < arg->width)
					write(fd, &c, 1);
			}
			*to_write += arg->width;
		}
		ft_putchar(0);
	}
}
