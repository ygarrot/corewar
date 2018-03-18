/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:34 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:26:56 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec_itoa(unsigned int value, char *base, char **str, int size)
{
	if (value / ft_strlen(base) == 0)
	{
		mallcheck(*str = (char*)malloc(sizeof(char) * size + 1));
		(*str)[size] = '\0';
		(*str)[size - 1] = base[value % ft_strlen(base)];
	}
	else
	{
		rec_itoa(value / ft_strlen(base), base, str, size + 1);
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

char		*ft_itoa_base(int value, char *base)
{
	char			*str;
	unsigned int	copy;
	int				size;

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
	rec_itoa(copy, base, &str, size);
	if (value < 0 && ft_strlen(base) == 10)
		str[0] = '-';
	return (my_strrev(str));
}
