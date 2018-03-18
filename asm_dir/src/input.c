/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:40:17 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/09 16:46:56 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		get_name(t_env *env, int fd, char **line)
{
	char	*ptr;

	if ((ptr = ft_strchr(*line, '\"')) == NULL)
		kill(env, "Can't get program name", 0);
	ptr++;
	while (!ft_strchr(ptr, '\"'))
	{
		if (!ptr)
			kill(env, "Error on program name", 0);
		if ((ft_strlcat(env->header->prog_name, ptr, PROG_NAME_LENGTH))
		>= PROG_NAME_LENGTH || (ft_strlcat(env->header->prog_name, "\n",
		PROG_NAME_LENGTH)) >= PROG_NAME_LENGTH)
			kill(env, "Program name too long", 0);
		ft_memdel((void**)line);
		if (get_next_line(fd, line) <= 0)
			kill(env, "Can't get program name", 0);
		ptr = *line;
		env->nb_line++;
	}
	ft_strreplace(ptr, '\"', '\0');
	if ((ft_strlcat(env->header->prog_name, ptr, PROG_NAME_LENGTH)) >=
	PROG_NAME_LENGTH)
		kill(env, "Program name too long", 0);
}

static void		get_comment(t_env *env, int fd, char **line)
{
	char	*ptr;

	if ((ptr = ft_strchr(*line, '\"')) == NULL)
		return ;
	ptr++;
	while (!ft_strchr(ptr, '\"'))
	{
		if (!ptr)
			kill(env, "Error on comment", 0);
		if ((ft_strlcat(env->header->comment, ptr, COMMENT_LENGTH))
		>= COMMENT_LENGTH || (ft_strlcat(env->header->comment, "\n",
		COMMENT_LENGTH)) >= COMMENT_LENGTH)
			kill(env, "Program comment too long", 0);
		ft_memdel((void**)line);
		if (get_next_line(fd, line) <= 0)
			kill(env, "Error on comment", 0);
		env->nb_line++;
		ptr = *line;
	}
	ft_strreplace(ptr, '\"', '\0');
	if ((ft_strlcat(env->header->comment, ptr, COMMENT_LENGTH)) >=
	COMMENT_LENGTH)
		kill(env, "Program comment too long", 0);
}

/*
** fonction de read sans gestion d'erreur
** gere juste les commentaires et les lignes vides
*/

void			read_loop(t_env *env, int fd)
{
	char		*line;
	t_line		*new_line;

	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_parse_str(line, LABEL_CHARS) || first_char_is_com(line))
			;
		else if (!ft_strncmp(my_trim(line), NAME_CMD_STRING,
				ft_strlen(NAME_CMD_STRING)))
			get_name(env, fd, &line);
		else if (!ft_strncmp(my_trim(line), COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
		{
			get_comment(env, fd, &line);
			env->comment = 1;
		}
		else
		{
			new_line = create_line(env, line);
			push_end_line(&env->list_lines, new_line);
		}
		ft_memdel((void**)&line);
		env->nb_line++;
	}
}

void			get_input(t_env *env, char *arg)
{
	if (!check_name(arg))
		kill(env, "Argument must be a valid .s file", 0);
	if ((env->fd = open(arg, O_RDONLY)) <= 0)
		kill(env, "Open error", 0);
	env->nb_line = 1;
	read_loop(env, env->fd);
	env->header->magic = COREWAR_EXEC_MAGIC;
	if (close(env->fd) == -1)
		kill(env, "Close error", 0);
}
