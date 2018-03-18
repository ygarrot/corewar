/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:24:00 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wcharlen(wchar_t wchar)
{
	if (wchar <= 0)
		return (0);
	if (wchar < 0x80)
		return (1);
	else if (wchar < 0x800)
		return (2);
	else if (wchar < 0x200000)
		return (3);
	else
		return (4);
}

size_t	ft_wstrlen(wchar_t *ws)
{
	size_t	i;

	i = 0;
	if (!ws)
		return (0);
	while (ws[i])
		i++;
	return (i);
}

void	convert_wchar_in_str(wchar_t wchar, char **str, int size)
{
	int i;

	i = 0;
	if (size == 1)
		(*str)[i++] = wchar;
	else if (size == 2)
	{
		(*str)[i++] = (wchar >> 6) + 0xC0;
		(*str)[i++] = (wchar & 0x3F) + 0x80;
	}
	else if (size == 3)
	{
		(*str)[i++] = (wchar >> 12) + 0xE0;
		(*str)[i++] = ((wchar >> 6) & 0x3F) + 0x80;
		(*str)[i++] = (wchar & 0x3F) + 0x80;
	}
	else
	{
		(*str)[i++] = (wchar >> 18) + 0xF0;
		(*str)[i++] = ((wchar >> 12) & 0x3F) + 0x80;
		(*str)[i++] = ((wchar >> 6) & 0x3F) + 0x80;
		(*str)[i++] = (wchar & 0x3F) + 0x80;
	}
	(*str)[i] = '\0';
}

void	add_wchar_in_str(wchar_t wchar, char **str)
{
	char	*tmp1;
	char	*tmp2;
	int		size;

	size = ft_wcharlen(wchar);
	mallcheck(tmp1 = (char*)malloc(sizeof(char) * size + 1));
	convert_wchar_in_str(wchar, &tmp1, size);
	tmp2 = ft_strjoin(*str, tmp1);
	free(*str);
	free(tmp1);
	*str = tmp2;
}

char	*ft_convert_wstr_in_str(wchar_t *wstr)
{
	char *str;

	str = ft_strnew(1);
	if (!wstr)
		return (0);
	while (*wstr)
	{
		add_wchar_in_str(*wstr, &str);
		wstr++;
	}
	return (str);
}
