/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallcheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 23:03:59 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 11:35:39 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		mallcheck(void *param)
{
	if (param == NULL)
	{
		ft_putendl_fd("Fail to malloc memory", 2);
		exit(EXIT_FAILURE);
	}
}
