/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:47:42 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/02/12 22:09:53 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#define B(x) begin->x
# define FLAGS g_flags
# define TYPS "sSpdDioOuUxXcCf"
# define UINTS "oux"
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

extern char		*g_flags;

typedef union	u_cast
{
	long double		F;
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
	char				*pr_data;
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

void			pars_star(t_vap_data_t *node);
void			pars_hash(t_vap_data_t *node);
void			pars_minus(t_vap_data_t *node);
void			pars_plus(t_vap_data_t *node);
void			pars_h(t_vap_data_t *node);
void			pars_l(t_vap_data_t *node);
void			pars_z(t_vap_data_t *node);
void			pars_j(t_vap_data_t *node);
void			pars_L(t_vap_data_t *node);
void			pars_aposrophe(t_vap_data_t *node);
void			pars_zero(t_vap_data_t *node);
void			pars_dot(t_vap_data_t *node);
void			pars_bax(t_vap_data_t *node);
void			pars_space(t_vap_data_t *node);
t_vap_data_t	*ft_make_vaplist(char *str);
void			pars_flags(t_vap_data_t *begin);
void			check_bax(t_vap_data_t *node);
char			*ft_find_type(char *str);
char			*itoa_base(unsigned long n, char type, int f);
long			ft_dvigai_tochku(long double n, int dot, int *intlen);
char			*ftoa(long n, int dot, int intlen);
void        	pr_data_for_nbr(t_vap_data_t *node);
void            read_pr_va_list(t_vap_data_t *begin, va_list args);

#endif
