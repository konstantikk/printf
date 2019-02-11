/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:46:52 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/02/07 21:33:48 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			read_pr_va_list(t_vap_data_t *begin, va_list args) //TODO
{
	while (begin)
	{
		begin->data = (t_cast *)malloc(16);
		if (begin->type == 'f')
		{
			if ((begin->size_flags)[2])
				begin->data->F = va_arg(args, long double);
			else
				begin->data->f = va_arg(args, double);
		}
		if (ft_strchr("id", begin->type))
		{
			if ((begin->size_flags)[1])
				begin->data->l = va_arg(args, long);
			else if ((begin->size_flags)[0] % 2)
				begin->data->h = va_arg(args, short);
			else if ((begin->size_flags)[0])
				begin->data->c = va_arg(args, char);
			else
				begin->data->i = va_arg(args, int);
		}
		if (ft_strchr("ouxX", begin->type))
		{
			if ((begin->size_flags)[1])
				begin->data->l = va_arg(args, unsigned long);
			else if ((begin->size_flags)[0] % 2)
				begin->data->h = va_arg(args, unsigned short);
			else if ((begin->size_flags)[0])
				begin->data->c = va_arg(args, unsigned char);
			else
				begin->data->i = va_arg(args, unsigned int);
		}
		if (ft_strchr("DOU", begin->type))
			begin->data->l = va_arg(args, long);
		if (begin->type == 'c')
			begin->data->c = va_arg(args, char);
		if (begin->type == 's')
			begin->data->p = va_arg(args, char *);
		if (begin->type == 'p')
			begin->data->p = va_arg(args, void *);
	begin = begin->next;
	}
}

int			take_val(t_vap_data_t *begin, int i)
{
	while (begin->ind != i)
		begin = begin->next;
	return (begin->data->i);
}

void		check_dot(t_vap_data_t *begin)
{
	t_vap_data_t	*node;

	node = begin;
	while (node)
	{

	}
}

void		create_pr_data(t_vap_data_t *begin)
{
	t_vap_data_t	*node;
	int				i;

	node = begin;
	while (begin)
	{
		begin->dot = begin->dot < 0 ? take_val(node, -begin->dot) : begin->dot;
		begin->width = begin->width < 0 ? take_val(node, -begin->width) : begin->width;
		if (begin->type == 'f')
		{
			if (begin->size_flags[2])
				begin->pr_data = ftoa(ft_dvigai_tochku(begin->data->F, begin->dot, &i), begin->dot, i);
			else
				begin->pr_data = ftoa(ft_dvigai_tochku(begin->data->f, begin->dot, &i), begin->dot, i);
		}
		if (ft_strchr("iduxX", begin->type))
		{
			if ((begin->size_flags)[1])
				begin->pr_data = itoa_base(begin->data->l, begin->type);
			else if ((begin->size_flags)[0])
				begin->pr_data = itoa_base((begin->size_flags)[0] % 2 ? begin->data->h : begin->data->c, begin->type);
			else
				begin->pr_data = itoa_base(begin->data->i, begin->type);
		}
		if (begin->type == 's')
			begin->pr_data = ft_strdup(begin->data->p);
		if (begin->type == 'c')
		{
			begin->pr_data = ft_strnew(1);
			(begin->pr_data)[0] = begin->data->c;
		}
		if (!(begin = begin->next))
			return ;
	}
}

#include <stdio.h>
void		ft_printf(char *str, ...)   //TODO dont work. need fix.
{
	t_vap_data_t	*begin;
	va_list			args;

	pars_flags((begin = ft_make_vaplist(str)));
	va_start(args, str);
	read_pr_va_list(begin, args);
	va_end(args);
	create_pr_data(begin);

	while (begin)
	{
		printf("_____\nnode : <%p>\n\ndata : <%hd>\npr_data : <%s>\nflags : <%s>\nstart : %s\nfinish : %s\nnext : <%p>\nind : %d\nwidth : %d\ndot : %d\nbax : %d\nsize_flags : %d %d %d\ntype : %c\nf_hash : %d\nf_apostrophe : %d\nf_minus : %d\nf_plus : %d\nf_space : %d\nf_star : %d\nf_dot : %d\nf_zero : %d\n",
				begin,B(data)->h,B(pr_data),B(flags), B(start),B(finish),B(next),B(ind),B(width),B(dot),B(bax),B(size_flags)[0],B(size_flags)[1],B(size_flags)[2],B(type),B(f_hash),B(f_apostrophe),B(f_minus),B(f_plus),B(f_space),B(f_star),B(f_dot),B(f_zero));
		begin = begin->next;
	}
	//printf ("%s\n,", ftoa(ft_dvigai_tochku(B(data), , ), , ))
}

int		main(int argc, char **argv) {
	ft_printf("%c %d %.*2$f", 'c', 10, 1.1111);
	//printf("\n\n\n%hhd", 100500);
	//printf("\n%ld", 9223372036854775098 - 9223372036854775097);
	//123.456
	//int i = 0;
	//printf("\n%s", ftoa(ft_dvigai_tochku(-123.12345, 4, &i), 4, i));
	return (0);
}
