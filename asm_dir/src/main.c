/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:14:11 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/09 18:51:02 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	kill(t_env *env, char *msg, int line)
{
	if (env)
	{
		free_lines(&env->list_lines);
		free_hash(env->hash_array);
		ft_memdel((void**)&env->header->prog_name);
		ft_memdel((void**)&env->header->comment);
		ft_memdel((void**)&env->header);
		ft_memdel((void**)&env->hash_array);
		ft_memdel((void**)&env);
	}
	if (msg && line)
		ft_dprintf(2, "%s line : %d\n", msg, line);
	else if (msg)
		ft_dprintf(2, "%s\n", msg);
	exit(msg ? EXIT_FAILURE : EXIT_SUCCESS);
}

t_env	*malloc_memory(void)
{
	t_env *env;

	mallcheck(env = (t_env*)ft_memalloc(sizeof(t_env)));
	mallcheck(env->header = (t_header*)ft_memalloc(sizeof(t_header)));
	mallcheck(env->hash_array = (t_list**)ft_memalloc(sizeof(t_list*)
		* MEM_SIZE));
	mallcheck(env->header->prog_name = (char*)ft_memalloc(sizeof(char) *
		PROG_NAME_LENGTH + 1));
	mallcheck(env->header->comment = (char*)ft_memalloc(sizeof(char) *
		COMMENT_LENGTH + 1));
	return (env);
}

int		main(int argc, char **argv)
{
	t_env		*env;

	env = NULL;
	if (argc == 2)
	{
		if (!check_defines())
		{
			ft_printf("Aaaaaaah on essaye de modifier les defines heins !!\n");
			return (-1);
		}
		env = malloc_memory();
		get_input(env, argv[1]);
		check_header(env);
		construct_hash_label(env);
		check_params(env);
		write_file(env, argv[1]);
		kill(env, 0, 0);
	}
	ft_dprintf(2, "Usage: ./asm <sourcefile.s>\n");
	return (1);
}
