/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:35:36 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/10 10:45:31 by jpriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		do_main(int ac, char **av)
{
	t_champs	*champ;
	t_vm		*vm;

	vm = init_vm();
	parse_entry(vm, ac, av);
	set_arena(vm);
	init_fc(vm);
	running(vm);
	check_process(vm);
	champ = vm->champs;
	while (champ && champ->num != vm->last_alive)
		champ = champ->next;
	if (!champ)
	{
		champ = vm->champs;
		while (champ->next)
			champ = champ->next;
	}
	(!vm->dump) ? dump_arena(vm) : 0;
	if (champ && vm->dump)
		ft_printf("Contestant %d, \"%s\", has won !\n",
			champ->num, champ->infos.name);
	erase_vm(vm);
}

int				main(int ac, char **av)
{
	if (!check_defines())
	{
		ft_printf("Aaaaaaah on essaye de modifier les defines heins !!\n");
		return (-1);
	}
	do_main(ac, av);
	return (0);
}
