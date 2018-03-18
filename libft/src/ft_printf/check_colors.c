/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:46:47 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/07 09:34:05 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_color(int fd, char **copy, char *str)
{
	write(fd, str, ft_strlen(str));
	while (**copy != '}')
		(*copy)++;
	(*copy)++;
	if (!**copy)
		exit(EXIT_SUCCESS);
}

void	check_colors(int fd, char **copy)
{
	if (ft_strncmp(*copy, "{red}", 5) == 0)
		print_color(fd, copy, RED_COLOR);
	else if (ft_strncmp(*copy, "{green}", 7) == 0)
		print_color(fd, copy, GREEN_COLOR);
	else if (ft_strncmp(*copy, "{yellow}", 8) == 0)
		print_color(fd, copy, YELLOW_COLOR);
	else if (ft_strncmp(*copy, "{blue}", 6) == 0)
		print_color(fd, copy, BLUE_COLOR);
	else if (ft_strncmp(*copy, "{magenta}", 9) == 0)
		print_color(fd, copy, MAGENTA_COLOR);
	else if (ft_strncmp(*copy, "{cyan}", 6) == 0)
		print_color(fd, copy, CYAN_COLOR);
	else if (ft_strncmp(*copy, "{eoc}", 5) == 0)
		print_color(fd, copy, COLOR_RESET);
}
