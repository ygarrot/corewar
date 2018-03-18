/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/07 11:45:13 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putnstr_fd(int fd, char *copy, size_t *n, int *to_write)
{
	if (copy)
	{
		write(fd, copy - *n, *n);
		*to_write += *n;
		*n = 0;
	}
}

int			write_loop(int fd, char *copy, va_list ap, int *write)
{
	int			ret;
	size_t		n;

	n = 0;
	while (*copy)
	{
		if (*copy == '{')
			check_colors(fd, &copy);
		if (*copy != '%')
			n++;
		else
		{
			if (n)
				ft_putnstr_fd(fd, copy, &n, write);
			ret = ft_arg(fd, &copy, ap, write);
			if (ret == -1 || ret == 0)
				return (ret);
		}
		copy++;
	}
	if (n)
		ft_putnstr_fd(fd, copy, &n, write);
	return (0);
}
