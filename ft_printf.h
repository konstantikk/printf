/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:47:42 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/02/17 05:49:56 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#define B(x) node->x
# define FLAGS g_flags
# define TYPS "sSpdDioOuUxXcCf"
# define UINTS "oux"
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

extern char		*g_flags;

typedef struct	s_vector
{
	char	*v;
	size_t	len;
	size_t	cap;
}				t_vector;

typedef union	u_cast
{
	long double		lf;
	double			f;
	long			l;
	void			*p;
	int 			i;
	short			h;
	char			c;
	unsigned        ui;
	unsigned char	uc;
	unsigned short	uh;
	unsigned long	ul;
}				t_cast;

typedef struct	s_vap_data_s
{
	t_cast				*data;
	t_vector			*pr_data;//////////////////
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
}				t_vap_data_t;

typedef union	u_ld
{
	long double		fn;
	unsigned long 			ln;
	short			hn[5];
	unsigned char	in[10];
}				t_ld;

void			pars_star(t_vap_data_t *node);
void			pars_hash(t_vap_data_t *node);
void			pars_minus(t_vap_data_t *node);
void			pars_plus(t_vap_data_t *node);
void			pars_h(t_vap_data_t *node);
void			pars_l(t_vap_data_t *node);
void			pars_z(t_vap_data_t *node);
void			pars_j(t_vap_data_t *node);
void			pars_ll(t_vap_data_t *node);/// pars_L
void			pars_aposrophe(t_vap_data_t *node);
void			pars_zero(t_vap_data_t *node);
void			pars_dot(t_vap_data_t *node);
void			pars_bax(t_vap_data_t *node);
void			pars_space(t_vap_data_t *node);
t_vap_data_t	*ft_make_vaplist(char *str);
void			pars_flags(t_vap_data_t *begin);
void			check_bax(t_vap_data_t *node);
char			*ft_find_type(char *str);
t_vector		*itoa_base(unsigned long n, char type, int f);
void        	pr_data_for_nbr(t_vap_data_t *node);
void            read_pr_va_list(t_vap_data_t *begin, va_list args);
t_vector		*long_pow(short digit, long power);
t_vector		*long_sum(t_vector *n1, t_vector *n2);
t_vector		*long_mult(t_vector *v1, t_vector *v2);
t_vector		*ft_ftoa(long double num);
int				take_exp(long double n, short *e, long *m);
char			*ft_strrev(char *str);
t_vector    	*makevec(void);
void       		pushbackvec(t_vector *v, char c);
t_vector		*pushfront_v(t_vector *v, size_t n, char c);
void        	fpw_for_integer(t_vap_data_t *node);
void            pars_float_pr_data(t_vap_data_t *node);
void			fpw_for_str(t_vap_data_t *node);

#endif
