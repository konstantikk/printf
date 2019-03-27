/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:49:31 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/20 05:43:19 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_base(char type)
{
	if (ft_strchr("diu", type))
		return (10);
	else if (type == 'x' || type == 'X' || type == 'p')
		return (16);
	else if (type == 'b')
		return (2);
	else
		return (8);
}

void		flags_mnpl(t_vap_l *node, t_string *vec, unsigned copy, int f)
{
	if (node->f_zero && node->f_dot)
		++node->f_zero;
	if ((size_t)node->dot > vec->len)
		vec_fast_pb(vec, '0', node->dot - vec->len);
	if ((size_t)node->width > vec->len)
		width_mnpl(node, vec, copy, f);
	else
	{
		hash_mnpl(node, vec, copy);
		if (f)
			vec_fast_pb(vec, '-', 1);
	}
	if (node->type == 'i' || node->type == 'd')
		spplus_mnpl(node, vec, copy, f);
}

t_string	*htoa(int n, t_vap_l *node)
{
	t_string		*vec;
	int				f;
	int				copy;

	f = 0;
	if (n < 0 && (n = -n))
		f = 1;
	copy = n;
	vec = makevec();
	if ((node->f_dot && node->dot != 0) || copy != 0 || !node->f_dot)
	{
		if (!n)
			vec_fast_pb(vec, '0', 1);
		while (n)
		{
			vec_fast_pb(vec, n % 10 + '0', 1);
			n /= 10;
		}
	}
	flags_mnpl(node, vec, copy, f);
	ft_strrev(vec->s);
	vec->cap = vec->len + 1;
	return (vec);
}

t_string	*itoa_base(unsigned long n, t_vap_l *node, int f)
{
	int				base;
	char			l;
	t_string		*vec;
	unsigned		copy;

	copy = n;
	base = find_base(node->type);
	vec = makevec();
	base == 2 && f && (n = (~n + 1));
	if ((node->f_dot && node->dot != 0) || copy != 0 || !node->f_dot)
	{
		if (!n)
			vec_fast_pb(vec, '0', 1);
		l = (char)(node->type == 'x' || node->type == 'p' ? 'a' : 'A');
		while (n)
		{
			vec_fast_pb(vec, (char)(n % base < 10 ? n % base + '0'
												: n % base % 10 + l), 1);
			n = n / base;
		}
	}
	flags_mnpl(node, vec, copy, f);
	ft_strrev(vec->s);
	vec->cap = vec->len + 1;
	return (vec);
}
