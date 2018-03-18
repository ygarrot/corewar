/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 12:53:53 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/06 10:40:00 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	core(t_vm *vm)
{
	int		i;
	char	**tab;

	if (COLS - (32 + 30 * vm->players) < 63)
		return ;
	wmove(vm->curs.haut, vm->curs.y, vm->curs.x + 30);
	wvline(vm->curs.haut, 0, (LINES / 5) - 2);
	tab = (char *[6])
	{" ,-----.                                                      ",
		"'  .--./  ,---.  ,--.--.  ,---.  ,--.   ,--.  ,--,--. ,--.--.",
		"|  |     | .-. | |  .--' | .-. : |  |.'.|  | ' ,-.  | |  .--' ",
		"'  '--'\\ ' '-' ' |  |    \\   --. |   .'.   | \\ '-'  | |  |    ",
		" `-----'  `---'  `--'     `----' '--'   '--'  `--`--' `--'    "};
	i = -1;
	while (++i < 5)
		mvwprintw(vm->curs.haut, i + 1, vm->curs.x + 31, tab[i]);
}

void	display_champs(t_vm *vm, t_champs *champs)
{
	int i;

	i = -1;
	while (++i < vm->players && (i > 1 || (32 + (30 * (i + 1))) < COLS))
	{
		vm->curs.y = ((32 + (30 * (i + 1))) < COLS) ? 1 : 5;
		vm->curs.x = ((32 + (30 * (i + 1))) < COLS) ? 32 + 30 * i :
			32 + 30 * ((i - 1) % 2);
		mvwprintw(vm->curs.haut, vm->curs.y, vm->curs.x,
				" Player %d: %.20s", champs->num, champs->infos.name);
		mvwprintw(vm->curs.haut, vm->curs.y + 1, vm->curs.x,
				" Lives For This Period :%4d", champs->lives);
		mvwprintw(vm->curs.haut, vm->curs.y + 2, vm->curs.x,
				" Last Live :%4d", champs->last_live);
		wmove(vm->curs.haut, vm->curs.y, vm->curs.x - 1);
		wvline(vm->curs.haut, 0, (LINES / 5) - 2);
		champs = champs->next;
	}
}

void	display_infos(t_vm *vm)
{
	wrefresh(vm->curs.haut);
	mvwprintw(vm->curs.haut, 1, 1, "Total Cycles : %d", vm->total_cycle);
	mvwprintw(vm->curs.haut, 2, 1, "Lives For This Period :%4d", vm->nbr_live);
	mvwprintw(vm->curs.haut, 3, 1, "Cycles/s LIM : %4d", vm->curs.wait);
	mvwprintw(vm->curs.haut, 4, 1, "Cycle To Die : %4d", vm->cycle_to_die);
	mvwprintw(vm->curs.haut, 5, 1, "PROCESS : %4d", vm->nb_process);
	display_champs(vm, vm->champs);
	core(vm);
	dis_refresh(&vm->curs);
	wrefresh(vm->curs.haut);
}

void	display_fc(t_vm *vm)
{
	int i;

	(vm->print & 32) ? ft_printf("nbr_live: %d\n", vm->nbr_live) : 0;
	if (vm->print)
		return ;
	vm->curs.color = 0;
	display_current(vm, 0, MEM_SIZE - 1);
	nodelay(stdscr, TRUE);
	if ((i = getch()))
		vm_pause(vm, i);
	display_infos(vm);
}

void	print_all(t_vm *vm, int div, int addr, int end)
{
	t_ncurses	*n;
	int			i;

	n = &vm->curs;
	i = get_lim(end < 0 ? -end : addr) - 1;
	while (++i < get_lim(end > 0 ? addr + end : -end + 1))
	{
		i = get_lim(i);
		n->y = (i / div) + 1;
		n->x = (i % div) + ((i % div) * 2) + 1;
		if (!(n->color_map[i] & 16) || end < 0)
		{
			n->color ? n->color_map[i] = n->color : 0;
			mvwprintw(n->bas, n->y, n->x, "%.2x", vm->map[i]);
			if (end == 4)
				mvwchgat(n->bas, n->y, n->x, 2, A_BOLD, n->color_map[i], 0);
			else if (end < 0 && (n->color_map[get_lim(addr)] &= 239))
			{
				mvwchgat(n->bas, n->y, n->x, 2, A_STANDOUT, n->color_map[i], 0);
				n->color_map[i] |= 16;
			}
			else if (!(n->color_map[i] & 16))
				mvwchgat(n->bas, n->y, n->x, 2, A_DIM, n->color_map[i], 0);
		}
	}
}
