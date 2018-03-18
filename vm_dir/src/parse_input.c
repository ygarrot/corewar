/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:42:16 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/10 10:02:46 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		name_is_champ(char *str)
{
	int		len;
	int		end;

	len = ft_strlen(str);
	end = 0;
	while (len && str[len--] != '.')
		end++;
	return (!(end != 4 || !ft_strcmp(&str[++end], ".cor")));
}

void	parse_header(t_vm *vm, t_champs *champs, char *str)
{
	int i;

	i = PROG_NAME_LENGTH + 4 + 8;
	if (*str || str[1] != (char)0xea
			|| str[2] != (char)0x83 || str[3] != (char)0xf3)
		exit_parsing(vm, "Error %s doesn't believe in fairies (no magic)\n",
				str);
	!str[4] ? exit_parsing(vm, "Error what's the %s's champ name ?\n", str) :
	err_malloc(vm, champs->infos.name = ft_strdup(&str[4]));
	champs->infos.size =
		get_nb_from_map((unsigned char*)str, PROG_NAME_LENGTH + 4, 8);
	str[i] ? err_malloc(vm, champs->infos.comment = ft_strdup(&str[i])) : 0;
}

void	parse_champ_file(t_vm *vm, t_champs *begin, char *str, int id_player)
{
	t_champs	*champs;
	int			head_size;
	int			fd;
	int			ret;

	head_size = PROG_NAME_LENGTH + COMMENT_LENGTH + 4 + 4 + 8;
	if (!(fd = open(str, O_RDONLY)) || fd < 0)
		exit_parsing(vm, "Error, couldn't open the file\n", NULL);
	champs = begin;
	while (champs->next)
		champs = champs->next;
	err_malloc(vm, champs->infos.file =
			ft_strnew(CHAMP_MAX_SIZE + head_size + 2));
	ret = read(fd, champs->infos.file, CHAMP_MAX_SIZE + head_size + 2);
	if (ret <= head_size || ret > (CHAMP_MAX_SIZE + head_size))
		exit_parsing(vm, ret <= head_size ? "%s doesnt have a good header size\
\n" : "%s is too large\n", str);
	parse_header(vm, champs, champs->infos.file);
	if (champs->infos.size != ret - head_size)
		exit_parsing(vm, "Error, File %s has a code size that"
						"differ from what its header says\n", str);
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", id_player,
		champs->infos.size, champs->infos.name, champs->infos.comment);
	close(fd) ? exit_parsing(vm, "Couldnt close %s\n", str) : 0;
}

int		parse_command(t_vm *vm, char **av, int i)
{
	int		num_champ;

	num_champ = 0;
	if (av[i + 1] != NULL && ft_str_isdigit(av[i + 1]))
	{
		if (!ft_strcmp(av[i], "-n"))
			ft_atoi(av[i + 1]) ? num_champ = ft_atoi(av[i + 1]) :
				exit_parsing(vm, "Number is not allowed\n", NULL);
		else if (!ft_strcmp(av[i], "-dump"))
			vm->dump = av[i + 1] ? ft_atoi(av[i + 1]) : -1;
		else if (!ft_strcmp(av[i], "-display"))
			vm->curs.display = av[i + 1] ? ft_atoi(av[i + 1]) : 0;
		else if (!ft_strcmp(av[i], "-show"))
			vm->print = ft_atoi(av[i + 1]);
		else
			exit_parsing(vm, "Unknown argument\n", NULL);
		return (num_champ ? num_champ : -3);
	}
	if (!ft_strcmp(av[i], "-show"))
		vm->print = 31;
	else if (!ft_strcmp(av[i], "-display"))
		vm->curs.display = 1;
	else
		exit_parsing(vm, "Error, Unknown argument\n", NULL);
	return (0);
}

void	parse_entry(t_vm *vm, int ac, char **av)
{
	int		i;
	int		com_num;

	ac < 2 ? exit_parsing(vm, NULL, NULL) : 0;
	com_num = 0;
	i = 0;
	ft_printf("Introducing contestants...\n");
	while (++i < ac)
	{
		if (name_is_champ(av[i]))
		{
			vm->players++;
			add_champs(vm, (com_num > 0) ? com_num : 0);
			parse_champ_file(vm, vm->champs, av[i], vm->players);
			com_num = 0;
		}
		else if ((com_num = parse_command(vm, av, i)))
			i++;
		com_num <= 0 ? com_num = 0 : 0;
	}
	if (com_num)
		exit_parsing(vm, "Unknown argument\n", NULL);
	if (vm->players <= 0 || vm->players > MAX_PLAYERS)
		exit_parsing(vm, vm->players < 1 ? "Error, not enough champions\n"
				: "Error, too much champions\n", NULL);
}
