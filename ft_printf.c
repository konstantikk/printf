/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:46:52 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/02/17 05:49:48 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			take_val(t_vap_data_t *begin, int i)
{
	while (begin->ind != i)
		begin = begin->next;
	return (begin->data->i);
}

void		create_pr_data(t_vap_data_t *begin)
{
	t_vap_data_t	*node;

	node = begin;
	while (begin)
	{
		begin->dot = begin->dot < 0 ? take_val(node, -begin->dot) : begin->dot;
		begin->width =
				begin->width < 0 ? take_val(node, -begin->width) : begin->width;
		if (begin->type == 'f')
		{
			if (begin->size_flags[2])
				begin->pr_data = ft_ftoa(begin->data->lf);
			else
				begin->pr_data = ft_ftoa(begin->data->f);
			pars_float_pr_data(begin);
		}
		else if (ft_strchr("idouxXpb", begin->type))
		{
			if (begin->type == 'p' && (begin->type = 'x') && ++(begin->size_flags[1]))
				++begin->f_hash;
			pr_data_for_nbr(begin);
			fpw_for_integer(begin);
		}
		else if (begin->type == 's')
		{	
			begin->pr_data = makevec();
			while (*(char*)(begin->data->p))
			   pushbackvec(begin->pr_data, *(char*)(begin->data->p));
			begin->pr_data->v = ft_strrev(begin->pr_data->v);
			fpw_for_str(begin);
		}
		else if (begin->type == 'c')
		{
			begin->pr_data = makevec();
			pushbackvec(begin->pr_data, begin->data->c);
			fpw_for_str(begin);
		}
		else
		{
			begin->pr_data = makevec();
			pushbackvec(begin->pr_data, begin->type);
			fpw_for_str(begin);
		}
		if (!(begin = begin->next))
			return ;
	}
}
#include <stdio.h>
void		round_float(t_vector **num, int dot)
{
	char	*i;
	char	*j;

	i = ft_strchr((*num)->v, '.') + dot + 1;
	j = i;
	if (j - (*num)->v > (*num)->len)
	{
		while ((*num)->len != j - (*num)->v)
		{
			pushbackvec(*num, '0');
			j = ft_strchr((*num)->v, '.') + dot + 1;
		}
	}
	else
	{
		if (*j > '5')
			*(--j) += 1;
		while (*j == ':')
		{
			*j-- = '0';
			if (*j == '.')
				--j;
			*j += 1;
			if (j == (*num)->v || *j == '-' + 1)
				break ;
		}
		(*num)->v[0] == ':' && ((*num)->v[0] = '1');
		if ((*num)->v[0] == '.' && ((*num)->v[0] = '1'))
			*num = pushfront_v(*num, 1, '-');
	}
	*(ft_strchr((*num)->v, '.') + dot + 1) = 0;
}

void 		pars_float_pr_data(t_vap_data_t *node)
{
	size_t	len;
	char	*i;

	i = ft_strchr(node->pr_data->v, '.');
	if (node->dot == 0)
		*(node->pr_data->v + (size_t)i + (node->f_hash ? 1 : 0)) = 0;
	else
		round_float(&(node->pr_data), node->dot);
	len = ft_strchr(node->pr_data->v, 0) - node->pr_data->v + 1;
	if (len < node->width)
	{
		if (!node->f_minus)
		{
			node->pr_data = pushfront_v(node->pr_data, node->width - len,
										node->f_zero ? '0' : ' ');
		} else
		{
			i = ft_strchr(node->pr_data->v, 0);
			while (len++ != node->width)
			{
				if (i - node->pr_data->v >= node->pr_data->len)
					pushbackvec(node->pr_data, 0);
				*i++ = ' ';
			}
			*i = 0;
		}
	}
	if (node->pr_data->v[0] != '-' && (node->f_plus || node->f_space))
		node->pr_data = pushfront_v(node->pr_data, 1, node->f_plus ? '+' : ' ');
}

#include <stdio.h>

void		ft_printf(char *str, ...)   //TODO dont work. need fix.
{
	t_vap_data_t	*begin;
	t_vap_data_t	*node;
	va_list			args;
node = begin;
	pars_flags((begin = ft_make_vaplist(str)));
	va_start(args, str);
	read_pr_va_list(begin, args);
	va_end(args);
	create_pr_data(begin);
	while (begin)
	{
		if (begin->f_star)
			continue ; 
		write(1, str, begin->start - str);
		write(1, begin->pr_data->v, ft_strchr(begin->pr_data->v, 0) - begin->start);
		str = begin->finish;
		begin = begin->next;
	}
	write(1, str, ft_strchr(str, 0) - str);
	printf("ya tut");
	while (node)
	{
		printf("_____\nnode : <%p>\n\ndata : <%hd>\npr_data : <%s>\nflags : <%s>\nstart : %s\nfinish : %s\nnext : <%p>\nind : %d\nwidth : %d\ndot : %d\nbax : %d\nsize_flags : %d %d %d\ntype : %c\nf_hash : %d\nf_apostrophe : %d\nf_minus : %d\nf_plus : %d\nf_space : %d\nf_star : %d\nf_dot : %d\nf_zero : %d\n",
				begin, B(data)->h, B(pr_data->v), B(flags), B(start), B(finish), B(next), B(ind), B(width), B(dot), B(bax), B(size_flags)[0], B(size_flags)[1], B(size_flags)[2], B(type), B(f_hash), B(f_apostrophe), B(f_minus), B(f_plus), B(f_space), B(f_star), B(f_dot), B(f_zero));
		node = node->next;
	}
}

int		main(int argc, char **argv) {
	t_vector *test1, *test2, *test;
	t_ld f;
	f.fn = -4096.l;

	int i = 0; /*;
	while (i < 16)
		printf("%hhd  ", f.in[i++]);
	printf("\n");*/
	f.fn = 12345.54321;/*
	if ((f.fn > 0. && f.fn < 1.))
		printf("\nqqq\n");*/
	short	e;
	unsigned long	m;

	take_exp(f.fn, &e, &m);
	//ft_printf("\n%f", 5.67);
	t_vector *v = ft_ftoa(f.fn);
	round_float(&v, 25);
	//printf("\n%s", v->v);
	//printf("\n%.25Lf", f.fn);
	ft_printf("\n%-15.3 0Lf %-0 100.50p", f.fn, v);
	//printf("\nkek%-15.3 0Lfkek |%-0 100.50p", f.fn, v);
	return (0);
}
