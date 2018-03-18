/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:55:56 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/26 17:20:45 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		null_write(int fd, int nb)
{
	char	tmp[1];
	int		i;

	tmp[0] = '\0';
	i = -1;
	while (++i < nb)
		write(fd, tmp, 1);
}

void		write_header(t_env *env, int fd)
{
	int		a;

	env->header->magic = little_to_big_endian(env->header->magic);
	a = (int)env->count;
	a = little_to_big_endian(a);
	write(fd, &env->header->magic, sizeof(int));
	write(fd, env->header->prog_name, ft_strlen(env->header->prog_name));
	null_write(fd, PROG_NAME_LENGTH - ft_strlen(env->header->prog_name) + 4);
	write(fd, &a, sizeof(int));
	write(fd, env->header->comment, ft_strlen(env->header->comment));
	null_write(fd, COMMENT_LENGTH - ft_strlen(env->header->comment) + 4);
}

void		write_params(t_env *env, t_line *c, int fd)
{
	int			i;
	char		*bit;
	int			size;

	i = -1;
	while (c->params[++i])
	{
		bit = split_bits(param_to_hex(env, c->params[i]));
		size = size_param(c, c->params[i], c->type_params[i]);
		while (size)
			write(fd, &(bit[size-- - 1]), 1);
		ft_memdel((void**)&bit);
	}
}

/*
** fonction principal de write. Parcours chaque ligne et ecrit les valeurs
** correspondante dans le fichier. Passage par split_bits pour l'endian.
*/

void		line_to_hex(t_env *env, int fd)
{
	t_line		*c;
	int			a;

	c = env->list_lines;
	env->count = 0;
	while (c)
	{
		if (c->op)
		{
			write(fd, &(g_op[i_tab(c->op)].opcode), 1);
			a = calc_instr_code(c);
			g_op[i_tab(c->op)].instr ? write(fd, &a, 1) : 0;
			write_params(env, c, fd);
			env->count += c->size;
		}
		c = c->next;
	}
}

void		write_file(t_env *env, char *arg)
{
	int		fd;

	if ((fd = create_file(arg)) <= 0)
		kill(env, "Fail to create file", 0);
	write_header(env, fd);
	line_to_hex(env, fd);
	if (close(fd) == -1)
		kill(env, "Fail to close file", 0);
}
