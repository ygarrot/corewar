/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:33 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 16:41:53 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		is_neg;
	long	result;

	result = 0;
	is_neg = 1;
	i = 0;
	while (*str == ' ' || (*str >= 8 && *str <= 13))
		str++;
	if (str[i] == '-')
		is_neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_is_num(str[i]))
	{
		while (ft_is_num(str[i]) && str[i])
		{
			result = (result * 10) - (str[i++] - '0');
			if (result > 0)
				return (is_neg == -1 ? 0 : -1);
		}
		return ((int)(result * (is_neg * -1)));
	}
	else
		return (0);
}
