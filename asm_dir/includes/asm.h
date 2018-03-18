/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:15:14 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/09 18:39:00 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_line
{
	struct s_line	*next;
	char			*label;
	char			*op;
	char			**params;
	int				*type_params;
	int				size;
	int				nb_line;
}					t_line;

typedef struct		s_env
{
	t_line			*list_lines;
	t_header		*header;
	t_list			**hash_array;
	unsigned int	count;
	int				comment: 2;
	int				fd;
	int				nb_line;
}					t_env;

/*
** fonctions de hash pour les labels
*/

int					search_hash(t_list **hash_array, char *label);
void				construct_hash_label(t_env *env);
int					size_param(t_line *current, char *word, int type);
void				free_hash(t_list **hash_array);
void				del_label(void *content, size_t content_size);
void				add_hash(t_list **hash_array, char *label,
int index);
void				print_hash(t_list **hash_array);
char				*label_name(char *label);

/*
** utils
*/

int					i_tab(char *str);
char				*get_next_word(char **line, char *sep);
void				kill(t_env *env, char *msg, int line);
int					find_label_type(char *label);
int					convert_binary_to_int(char *tmp);
int					first_char_is_com(char *str);
int					is_label(char *word);

/*
** input
*/

void				get_input(t_env *env, char *arg);
void				add_param(t_env *env, t_line *new_line,
char *word, int code);
int					find_param_type(char *param);
char				*my_trim(char *str);

/*
** debug
*/

void				print_lines(t_line *lines);
void				print_line(t_line *line);

/*
** list et create_line
*/

void				free_lines(t_line **lines);
void				push_end_line(t_line **head, t_line *new_line);
t_line				*create_line(t_env *env, char *ptr);
t_line				*multi_line_label(t_env *env, t_line *new_line);
t_line				*fill_line(t_env *env, t_line *new_line, char *ptr);
void				get_label(t_env *env, t_line *new_line, char *word);

/*
** write
*/

void				write_file(t_env *env, char *arg);
void				line_to_hex(t_env *env, int fd);
int					create_file(char *file);
int					param_to_hex(t_env *env, char *param);
int					calc_instr_code(t_line *current);
void				fill_tmp(int type, char tmp[9], int *i_tmp);

/*
** handle endian
*/

int					little_to_big_endian(int x);
char				*split_bits(int x);

/*
** check
*/

void				check_header(t_env *env);
int					check_name(char *str);
void				check_params(t_env *env);
void				check_line(t_env *env, t_line *line);
int					check_defines(void);

#endif
