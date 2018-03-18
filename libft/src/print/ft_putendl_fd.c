/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:43 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:48:37 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	int i;

	if (!s || fd < 0)
		return ;
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
	write(fd, "\n", 1);
}
