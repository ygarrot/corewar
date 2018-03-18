/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:47:09 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/22 11:12:09 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <inttypes.h>
# include "libft.h"

# define CHAR 1
# define INT 2
# define STR 3
# define U_INT 4

# define RED_COLOR     "\x1b[31m"
# define GREEN_COLOR   "\x1b[32m"
# define YELLOW_COLOR  "\x1b[33m"
# define BLUE_COLOR    "\x1b[34m"
# define MAGENTA_COLOR "\x1b[35m"
# define CYAN_COLOR    "\x1b[36m"
# define COLOR_RESET   "\x1b[0m"
# define JOIN_END 1
# define JOIN_START 2
# define STAR_PREC 1
# define STAR_WIDTH 2

typedef enum	e_taille
{
	h = 1,
	hh,
	z,
	l,
	ll,
	j
}				t_taille;

typedef struct	s_arg
{
	char		*str;
	int			width;
	int			prec;
	int			var_type;
	char		type;
	int			star;
	int			char_null :2;
	int			sharp :2;
	int			zero :2;
	int			space :2;
	int			plus :2;
	int			minus :2;
	t_taille	lenght;
}				t_arg;

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_vdprintf(int fd, const char *format, va_list ap);
int				ft_arg(int fd, char **copy, va_list ap, int *write);
void			get_str(va_list ap, t_arg *arg);
void			get_str_nb(va_list ap, t_arg *arg);
void			get_str_u_nb(va_list ap, t_arg *arg);
void			get_str_str(va_list ap, t_arg *arg);
void			get_str_char(va_list ap, t_arg *arg);
void			print_arg(int fd, t_arg *arg, int *write);
void			conflict(t_arg *arg);
void			get_vartype(t_arg *arg);
void			analyse(char **copy, t_arg *arg, va_list ap);
void			modif_str(t_arg *arg);
void			add_str(char **str, char type, int number, int start);
void			handle_sign(t_arg *arg);
void			handle_sharp(t_arg *arg);
void			handle_width(t_arg *arg);
void			handle_prec(t_arg *arg);
char			*ft_lltoa_base(long long int value, char *base);
char			*ft_ulltoa_base(unsigned long long int value, char *base);
void			str_join_n_free(char *to_add, char **src, int type);
void			str_cut_first_n_free(char **str, int nb);
char			*ft_convert_wstr_in_str(wchar_t *ws);
size_t			ft_wstrlen(wchar_t *ws);
int				ft_wcharlen(wchar_t c);
void			check_colors(int fd, char **copy);
void			get_with_star(va_list ap, t_arg *arg, int code);
int				write_loop(int fd, char *copy, va_list ap, int *write);
void			ft_putnstr_fd(int fd, char *copy, size_t *n, int *to_write);
#endif
