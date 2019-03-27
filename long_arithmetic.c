/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:39:20 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/02/18 23:50:31 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		l_mul(t_string *v, char c)
{
	char *str;
	char next_r;

	str = v->s;
	next_r = 0;
	c = c - '0';
	while (*str || next_r)
	{
		if (!*str)
		{
			vec_fast_pb(v, next_r % 10 + '0', 1);
			next_r /= 10;
			str = v->s + v->len;
			continue ;
		}
		*str = (*str - '0') * c + next_r;
		next_r = *str / 10;
		*str = *str % 10 + '0';
		++str;
	}
}

t_string	*long_pow(short digit, long power)
{
	t_string	*r;

	r = makevec();
	digit += '0';
	vec_fast_pb(r, digit, 1);
	while (--power)
		l_mul(r, digit);
	return (r);
}

t_string	*long_sum(t_string *n1, t_string *n2)
{
	char		carry;
	t_string	*rv;
	size_t		i;

	carry = 0;
	i = 0;
	if (n1->len < n2->len)
	{
		rv = n1;
		n1 = n2;
		n2 = rv;
	}
	rv = makevec();
	while (i < n1->len)
	{
		carry += n1->s[i] - '0' + (i < n2->len ? n2->s[i] - '0' : 0);
		vec_fast_pb(rv, carry % 10 + '0', 1);
		carry /= 10;
		++i;
	}
	if (carry)
		vec_fast_pb(rv, carry % 10 + '0', 1);
	free_vec(&n1);
	free_vec(&n2);
	return (rv);
}

t_string	*long_mult(t_string *v1, t_string *v2)
{
	size_t		i;
	t_string	*rv;
	t_string	*hv;

	if (v2->len > v1->len)
	{
		rv = v1;
		v1 = v2;
		v2 = rv;
	}
	rv = makevec();
	vec_fast_pb(rv, '0', 1);
	i = 0;
	while (i < v2->len)
	{
		hv = ft_makestr(v1->s, v1->len, v1->cap);
		l_mul(hv, v2->s[i]);
		hv = pushfront_v(hv, i, '0');
		rv = long_sum(rv, hv);
		i++;
	}
	free_vec(&v1);
	free_vec(&v2);
	return (rv);
}
