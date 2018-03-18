/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:32:33 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/02 19:16:34 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		little_to_big_endian(int x)
{
	x = ((x & 0xFFFF) << 16) | ((x & 0xFFFF0000) >> 16);
	x = ((x & (0xFF00FF)) << 8) | ((x & 0xFF00FF00) >> 8);
	return (x);
}

/*
** store chaque bit de l'int pour les print dans le bon ordre
*/

char	*split_bits(int x)
{
	char	*bit;

	bit = (char*)malloc(sizeof(char) * 4);
	if (!bit)
		return (NULL);
	bit[0] = (char)(x & 0x000000FF);
	bit[1] = (char)((x & 0x0000FF00) >> 8);
	bit[2] = (char)((x & 0x00FF0000) >> 16);
	bit[3] = (char)((x & 0xFF000000) >> 24);
	return (bit);
}
