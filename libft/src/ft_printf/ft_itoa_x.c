/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_X.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:23:40 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec_itoa_ll(unsigned long long int value, char *base,
char **str, int size)
{
	if (value / ft_strlen(base) == 0)
	{
		mallcheck(*str = (char*)malloc(sizeof(char) * size + 1));
		(*str)[size] = '\0';
		(*str)[size - 1] = base[value % ft_strlen(base)];
	}
	else
	{
		rec_itoa_ll(value / ft_strlen(base), base, str, size + 1);
		(*str)[size - 1] = base[value % ft_strlen(base)];
	}
}

static char	*my_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	len = ft_strlen(str);
	i = 0;
	if (str[i] == '-')
		i++;
	while (i < --len)
	{
		tmp = str[len];
		str[len] = str[i];
		str[i++] = tmp;
	}
	return (str);
}

char		*ft_lltoa_base(long long int value, char *base)
{
	char						*str;
	int							size;
	unsigned long long int		copy;

	if (value < 0)
	{
		if (ft_strlen(base) == 10)
			copy = -value;
		else
			copy = value + 4294967296;
	}
	else
		copy = value;
	size = (value < 0 && ft_strlen(base) == 10) ? 2 : 1;
	rec_itoa_ll(copy, base, &str, size);
	if (value < 0 && ft_strlen(base) == 10)
		str[0] = '-';
	return (my_strrev(str));
}

char		*ft_ulltoa_base(unsigned long long int value, char *base)
{
	char *str;

	rec_itoa_ll(value, base, &str, 1);
	return (my_strrev(str));
}
