/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_defines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 18:38:24 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/09 18:53:18 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_defines(void)
{
	if (MAX_PLAYERS <= 0 || MAX_PLAYERS > 8)
		return (0);
	if (REG_CODE < 0 || DIR_CODE < 0 || IND_CODE < 0 || IND_SIZE < 0
		|| REG_SIZE < 0 || T_REG < 0 || T_DIR < 0 || T_IND < 0 ||
		T_LAB < 0)
		return (0);
	if (PROG_NAME_LENGTH < 0 || COMMENT_LENGTH < 0 || REG_NUMBER < 0 ||
		CYCLE_TO_DIE < 0 || NBR_LIVE < 0 || MAX_CHECKS < 0 || CYCLE_DELTA < 0)
		return (0);
	return (1);
}
