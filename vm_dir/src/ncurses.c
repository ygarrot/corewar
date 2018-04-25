/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:03:20 by ygarrot           #+#    #+#             */
/*   Updated: 2018/04/20 16:38:25 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	shortcut(t_vm *vm, int key)
{
	t_ncurses	*n;

	n = &vm->curs;
	if (key == 27)
	{
		erase_vm(vm);
		endwin();
		exit(1);
	}
	if (key == '1' && (n->wait - 10) > 0)
		n->wait -= 10;
	if (key == '2' && (n->wait - 1) > 0)
		n->wait--;
	if (key == '4' && (n->wait + 10) <= 1000)
		n->wait += 10;
	if (key == '3' && (n->wait + 1) <= 1000)
		n->wait++;
}

void	vm_pause(t_vm *vm, int key)
{
	int next_key;

	next_key = 0;
	if (key == 32)
		while (next_key != 32)
		{
			nodelay(stdscr, FALSE);
			next_key = getch();
			next_key != 32 ? shortcut(vm, next_key) : 0;
			display_infos(vm);
		}
	key == 32 ? 0 : shortcut(vm, key);
	nodelay(stdscr, TRUE);
}

void	display_current(t_vm *vm, int addr, int end)
{
	int		div;
	int		wait;

	div = COLS - 2;
	div = (div / 3) + ((div % 3 > 1) * 2);
	print_all(vm, div, addr, end);
	dis_refresh(&vm->curs);
	wrefresh(vm->curs.bas);
	wait = MICRO / ((vm->curs.wait >= 0) ? vm->curs.wait : 0);
//	usleep(wait);
}

void	dis_refresh(t_ncurses *n)
{
	if (COLS == n->l_cols && LINES == n->l_lines)
		return ;
	werase(n->haut);
	werase(n->bas);
	endwin();
	n->bas = subwin(stdscr, (LINES * 4) / 5, COLS, (LINES * 1) / 5, 0);
	n->haut = subwin(stdscr, (LINES * 1) / 5, COLS, 0, 0);
	box(n->bas, ACS_VLINE, ACS_HLINE);
	box(n->haut, ACS_VLINE, ACS_HLINE);
	n->l_lines = LINES;
	n->l_cols = COLS;
}

void	init_ncurses(t_vm *vm)
{
	initscr();
	vm->fd = open("/dev/ttys004", O_RDWR);
	vm->curs.display = 1;
	dis_refresh(&vm->curs);
	vm->curs.wait = 50;
	curs_set(0);
	start_color();
	use_default_colors();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	noecho();
	display_current(vm, 0, MEM_SIZE - 1);
}
