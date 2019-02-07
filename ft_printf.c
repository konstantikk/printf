/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:46:52 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/02/01 23:14:37 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//qwe%lll012d %f tewtw%*.* *7$#2$lhlhlhzii
typedef union	u_cast
{
	long double	Lf;
	double		f;
	long		li;
	void		*p;
	int 		i;
	short		hi;
	char		c;
	struct
	{
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;
		unsigned char b5 : 1;
		unsigned char b6 : 1;
		unsigned char b7 : 1;
		unsigned char b8 : 1;
	}			b[16];
}				t_cast;

void			read_pr_va_list(t_vap_data_t *begin, va_list args) //TODO
{
	double			f;
	long double		Lf;
	char			c;
	short int		hi;
	int				i;
	long int		li;

	if (begin->type == 'f')
	{
		begin->data = malloc((begin->size_flags)[2] ? 16 : 8);
		if ((begin->size_flags)[2] && (Lf = va_arg(args, long double)))
			ft_memcpy(begin->data, &Lf, 16);
		if (!(begin->size_flags)[2] && (f = va_arg(args, double)))
			ft_memcpy(begin->data, &f, 8);
		return ;
	}
	if (ft_strchr("idouxX", begin->type))
	{}
	if (ft_strchr("DOU", begin->type))
	{}
	if (ft_strchr("cs", begin->type))
	{}
	if (ft_strchr("CS", begin->type))
	{}
	if (begin->type == 'p')
	{}
}

/*
vap_data_t	*ft_initialize_valist(vap_data_t *begin)
{

}
*/
#include <stdio.h>
void		ft_printf(char *str, ...)   //TODO dont work. need fix.
{
	t_vap_data_t	*begin;
	va_list			args;

	pars_flags((begin = ft_make_vaplist(str)));
	va_start(args, str);
	//read_pr_va_list(begin, args);

	while (begin)
	{
		printf("_____\nnode : <%p>\n\ndata : <%p>\npr_data : <%s>\nflags : <%s>\nstart : %s\nfinish : %s\nnext : <%p>\nind : %d\nwidth : %d\ndot : %d\nbax : %d\nsize_flags : %d %d %d\ntype : %c\nf_hash : %d\nf_apostrophe : %d\nf_minus : %d\nf_plus : %d\nf_space : %d\nf_star : %d\nf_dot : %d\nf_zero : %d\n",
				begin,B(data),B(pr_data),B(flags), B(start),B(finish),B(next),B(ind),B(width),B(dot),B(bax),B(size_flags)[0],B(size_flags)[1],B(size_flags)[2],B(type),B(f_hash),B(f_apostrophe),B(f_minus),B(f_plus),B(f_space),B(f_star),B(f_dot),B(f_zero));
		begin = begin->next;
	}

}


int		main(int argc, char **argv) {
	ft_printf(argv[1]);
	return (0);
}
//printf("%f %1500ld %2$ld" , 1.0, 5000000000);
