/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:47:42 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/02/19 19:12:10 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define PRV node->pr_data
# define FLAGS g_flags
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

extern char		*g_flags;

typedef union	u_cast
{
	long double		lf;
	double			f;
	long			l;
	void			*p;
	int				i;
	short			h;
	char			c;
	unsigned		ui;
	unsigned char	uc;
	unsigned short	uh;
	unsigned long	ul;
}				t_cast;

typedef struct	s_vap_data_s
{
	t_cast				*data;
	t_string			*pr_data;
	char				*flags;
	char				*start;
	char				*finish;
	struct s_vap_data_s	*next;
	int					ind;
	int					width;
	int					dot;
	int					bax;
	int					size_flags[3];
	char				type;
	unsigned			f_hash : 1;
	unsigned			f_apostrophe : 1;
	unsigned			f_minus : 1;
	unsigned			f_plus : 1;
	unsigned			f_space : 1;
	unsigned			f_star : 1;
	unsigned			f_dot : 1;
	unsigned			f_zero : 1;
}				t_vap_l;

typedef union	u_ld
{
	long double				fn;
	unsigned long			ln;
	short					hn[5];
}				t_ld;

int				ft_printf(char *format, ...);

void			pars_star(t_vap_l *node);
void			pars_hash(t_vap_l *node);
void			pars_minus(t_vap_l *node);
void			pars_plus(t_vap_l *node);
void			pars_h(t_vap_l *node);
void			pars_l(t_vap_l *node);
void			pars_z(t_vap_l *node);
void			pars_j(t_vap_l *node);
void			pars_ll(t_vap_l *node);
void			pars_aposrophe(t_vap_l *node);
void			pars_zero(t_vap_l *node);
void			pars_dot(t_vap_l *node);
void			pars_bax(t_vap_l *node);
void			pars_space(t_vap_l *node);
void			pars_flags(t_vap_l *begin);
void			check_bax(t_vap_l *node);
void			help_pars_star(t_vap_l *node, int ind);
void			create_star_nod(t_vap_l *node, int n);

void			trash_pr_data(t_vap_l *node);
void			char_pr_data(t_vap_l *node);
void			string_pr_data(t_vap_l *node);
void			int_pr_data(t_vap_l *node);
void			float_pr_data(t_vap_l *node);

void			read_pr_va_list(t_vap_l *begin, va_list args);
t_vap_l			*ft_make_vaplist(char *str);
t_vap_l			*free_vap_list(t_vap_l *begin);

void			create_pr_data(t_vap_l *begin);
char			*ft_find_type(char *str);
void			pr_data_for_nbr(t_vap_l *node);
void			pars_float_pr_data(t_vap_l *node);
void			fpw_for_str(t_vap_l *node);

void			l_mul(t_string *v, char c);
t_string		*long_pow(short digit, long power);
t_string		*long_sum(t_string *n1, t_string *n2);
t_string		*long_mult(t_string *v1, t_string *v2);

int				take_exp(long double n, short *e, unsigned long *m);
t_string		*ft_ftoa(long double num);
t_string		*itoa_base(unsigned long n, t_vap_l *node, int f);
t_string		*htoa(int n, t_vap_l *node);

char			*ft_strrev(char *str);
void			vec_fast_pb(t_string *str, char c, size_t len);
t_string		*makevec(void);
t_string		*pushfront_v(t_string *v, size_t n, char c);
void			free_vec(t_string **v);

void			hash_mnpl(t_vap_l *node, t_string *vec, unsigned copy);
void			spplus_mnpl(t_vap_l *node, t_string *vec, unsigned copy, int f);
void			minus_mnpl(t_vap_l *node, t_string *vec, unsigned copy, int f);
void			zero_mnpl(t_vap_l *node, t_string *vec, unsigned copy, int f);
void			width_mnpl(t_vap_l *node, t_string *vec, unsigned copy, int f);
void			flags_mnpl(t_vap_l *node, t_string *vec, unsigned copy, int f);

#endif
