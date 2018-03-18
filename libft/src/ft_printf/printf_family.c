/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_family.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 11:41:30 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/07 11:48:12 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vdprintf(1, format, ap);
	va_end(ap);
	return (ret);
}

int			ft_vprintf(const char *format, va_list ap)
{
	int			ret;

	ret = ft_vdprintf(1, format, ap);
	return (ret);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

int			ft_vdprintf(int fd, const char *format, va_list ap)
{
	char	*copy;
	int		write;
	int		ret;

	copy = (char*)format;
	write = 0;
	ret = write_loop(fd, copy, ap, &write);
	return (ret == -1 ? ret : write);
}
