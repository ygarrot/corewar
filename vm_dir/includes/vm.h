/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:57:41 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/18 09:42:16 by jpriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include <ncurses.h>

# define S 2
# define P 1
# define T 0
# define MICRO 1000000

typedef struct	s_infos
{
	char	*name;
	char	*comment;
	char	*file;
	int		size;
}				t_infos;

typedef struct	s_instr
{
	int		params[3][MAX_ARGS_NUMBER];
	int		cycle;
	int		opcode;
	int		w_infos;
}				t_instr;

typedef struct	s_process
{
	int					color;
	int					number;
	int					pc;
	int					next_pc;
	int					live;
	int					last_live;
	int					carry;
	int					regs[16];
	t_instr				*instr;
	struct s_process	*next;
}				t_process;

typedef struct	s_champs
{
	int				color;
	int				num;
	int				lives;
	int				last_live;
	t_infos			infos;
	struct s_champs	*next;
}				t_champs;

typedef struct	s_ncurses
{
	int			color_map[MEM_SIZE];
	int			display;
	int			l_cols;
	int			l_lines;
	int			wait;
	char		color;
	int			y;
	int			x;
	WINDOW		*bas;
	WINDOW		*haut;
}				t_ncurses;

typedef struct	s_vm
{
	int				fd;
	unsigned char	*map;
	int				nb_process;
	int				total_process;

	int				dump;
	int				print;
	int				players;
	int				nbr_live;

	int				cycle;
	int				total_cycle;
	int				cycle_to_die;
	int				last_check;
	int				last_alive;
	void			(*fc_tab[17])(struct s_vm*, t_instr*, t_process*);
	t_process		*process;
	t_champs		*champs;
	t_ncurses		curs;
}				t_vm;

/*
** ncurses
*/

void			display_fc(t_vm *vm);
void			init_col(void);
void			display_current(t_vm *vm, int addr, int end);
void			init_ncurses(t_vm *vm);
void			dis_refresh(t_ncurses *n);
void			shortcut(t_vm *vm, int key);
void			core(t_vm *vm);
void			display_champs(t_vm *vm, t_champs *champs);
void			vm_pause(t_vm *vm, int key);
void			display_infos(t_vm *vm);
void			print_all(t_vm *vm, int div, int addr, int end);

/*
**init.c
*/

void			add_champs(t_vm *vm, int num);
t_vm			*init_vm(void);
int				add_instr(t_instr *instr, t_instr *toadd);
int				init_instr(t_instr *instr);

int				add_process(t_champs *champs);
t_process		*init_process(t_vm *vm);

/*
** parse_entry.c
*/

void			parse_entry(t_vm *vm, int ac, char **av);
int				parse_command(t_vm *vm, char **av, int i);
void			parse_champ_file(t_vm *vm, t_champs *begin, char *str,
					int id_player);
void			parse_header(t_vm *vm, t_champs *champs, char *str);
int				name_is_champ(char *str);

void			set_arena(t_vm *vm);
void			init_queue(t_vm *vm);

/*
**erase.c
*/

void			kill_process(t_process **todel);
void			erase_champ(t_champs *champs);
void			erase_vm(t_vm *vm);
void			exit_parsing(t_vm *vm, char *str, char *arg);

/*
**running.c
*/

void			running(t_vm *vm);
void			check_lives(t_vm *vm);
void			check_process(t_vm *vm);
void			check_1st_process(t_vm *vm);

void			execute_process(t_vm *vm);

/*
**decode_utils.c
*/

int				get_lim(int temp);
char			*convert_to_binary(t_vm *vm, unsigned char a);
void			decode_byte(t_instr *instr, char *byte);
int				get_nb_from_map(unsigned char *map, int addr, int nb_bytes);
void			write_int_to_map(t_vm *vm, int addr, int x);
int				manage_neg(int value, int size);

void			fetch_instr2(t_vm *vm, t_process *process);
void			fetch_instr(t_vm *vm, t_process *process);

void			err_malloc(t_vm *vm, void *param);

t_champs		*search_champs(t_vm *vm, int num);
void			process_dup(t_vm *vm, t_process *p, int new_pc);

void			display_arena(t_vm *vm);
void			dump_arena(t_vm *vm);

int				get_param_value(t_vm *vm, t_process *process, int index);

int				check_reg(int tab[3][MAX_ARGS_NUMBER], int index);
int				valide_op(t_instr *instr);
int				valide_instr(t_instr *instr);
void			print_pc_advance(t_vm *vm, t_process *process);

/*
**fc
*/

void			init_fc(t_vm *vm);
void			ft_live(t_vm *vm, t_instr *i, t_process *p);
void			ft_ld(t_vm *vm, t_instr *i, t_process *p);
void			ft_st(t_vm *vm, t_instr *i, t_process *p);

/*
**fc_2
*/

void			ft_add(t_vm *vm, t_instr *i, t_process *p);
void			ft_sub(t_vm *vm, t_instr *i, t_process *p);
void			ft_and(t_vm *vm, t_instr *i, t_process *p);
void			ft_or(t_vm *vm, t_instr *i, t_process *p);
void			ft_xor(t_vm *vm, t_instr *i, t_process *p);

/*
**fc_3
*/

void			ft_zjmp(t_vm *vm, t_instr *i, t_process *p);
void			ft_ldi(t_vm *vm, t_instr *i, t_process *p);
void			ft_sti(t_vm *vm, t_instr *i, t_process *p);
void			ft_fork(t_vm *vm, t_instr *i, t_process *p);
void			ft_lld(t_vm *vm, t_instr *i, t_process *p);

/*
**fc_4
*/

void			ft_lldi(t_vm *vm, t_instr *i, t_process *p);
void			ft_lfork(t_vm *vm, t_instr *i, t_process *p);
void			ft_aff(t_vm *vm, t_instr *i, t_process *p);
void			ft_pass(t_vm *vm, t_instr *i, t_process *p);

/*
** check_error.c
*/

int				check_defines(void);

#endif
