/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:24:32 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**Ces fonctions recuperent l argument de type str ou char
**et le renvoie en char*
*/

/*
** gere la precision tout de suite pour les wchar_t
**pour eviter de couper au milieu d'un caractere
*/

void		handle_prec_wstr(wchar_t **tmp, t_arg *arg)
{
	wchar_t		*new;
	int			i;
	int			len;
	int			j;

	if (arg->prec > 0 && (size_t)arg->prec < ft_wstrlen(*tmp))
	{
		len = 0;
		i = 0;
		while (len <= arg->prec)
		{
			len += ft_wcharlen((*tmp)[i]);
			i++;
		}
		mallcheck(new = (wchar_t*)malloc(sizeof(wchar_t) * i));
		j = -1;
		while (++j < i - 1)
			new[j] = (*tmp)[j];
		new[j] = '\0';
		*tmp = new;
	}
}

void		get_str_str(va_list ap, t_arg *arg)
{
	wchar_t *tmp;

	if (arg->type == 's')
		arg->str = ft_strdup(va_arg(ap, char*));
	if (arg->type == 'S')
	{
		tmp = va_arg(ap, wchar_t*);
		handle_prec_wstr(&tmp, arg);
		arg->str = ft_convert_wstr_in_str(tmp);
	}
	if (arg->str == NULL)
		arg->str = ft_strdup("(null)");
	if (arg->prec < 0)
		ft_strclr(arg->str);
}

void		get_str_char(va_list ap, t_arg *arg)
{
	char	*str;
	wchar_t	wstr[2];

	if (arg->type == 'c')
	{
		mallcheck(str = (char*)malloc(2));
		str[0] = (char)va_arg(ap, int);
		str[1] = '\0';
		if (!str[0])
			arg->char_null = 1;
		arg->str = str;
	}
	if (arg->type == 'C')
	{
		wstr[0] = (wchar_t)va_arg(ap, wchar_t);
		wstr[1] = '\0';
		if (!wstr[0])
			arg->char_null = 1;
		str = ft_convert_wstr_in_str(wstr);
		arg->str = str;
	}
}
