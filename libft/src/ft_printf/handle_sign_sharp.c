/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sign_sharp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/07 09:18:32 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_sign(t_arg *arg)
{
	if (arg->plus && arg->str[0] != '-')
		add_str(&(arg->str), '+', 1, 1);
	if (arg->space && arg->str[0] != '-')
		add_str(&(arg->str), ' ', 1, 1);
}

void	handle_sharp(t_arg *arg)
{
	if (arg->sharp)
	{
		if (ft_strlen(arg->str) == 1 && arg->str[0] == '0' && arg->type != 'p')
			return ;
		if ((arg->type == 'x' || arg->type == 'X') && !arg->str[0])
			return ;
		if (arg->type == 'o' && arg->str[0] == '0')
			return ;
		if (arg->type == 'o')
			str_join_n_free("0", &arg->str, JOIN_START);
		else if (arg->type == 'X')
			str_join_n_free("0X", &arg->str, JOIN_START);
		else if (arg->type == 'p' || arg->type == 'x')
			str_join_n_free("0x", &arg->str, JOIN_START);
		else if (arg->type == 'b')
			str_join_n_free("0b", &arg->str, JOIN_START);
	}
}
