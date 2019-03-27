/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:49:31 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/19 19:01:13 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			take_exp(long double n, short *e, unsigned long *m)
{
	int			i;
	t_ld		f;

	f.fn = n;
	*e = f.hn[4] & (short)32767;
	if (m)
		*m = f.ln;
	i = f.hn[4] == *e;
	return (i);
}

t_string	*ft_utoa(unsigned long n)
{
	t_string	*r;

	r = makevec();
	if (!n)
		vec_fast_pb(r, '0', 1);
	while (n)
	{
		vec_fast_pb(r, n % 10 + '0', 1);
		n /= 10;
	}
	return (r);
}

t_string	*check_inf_nan(long double num)
{
	int				i;
	short			e;
	unsigned long	m;
	t_string		*rv;

	i = take_exp(num, &e, &m);
	if (m == 0x8000000000000000L)
	{
		if (!i)
			rv = pushfront_v(ft_makestr("inf", 3, 5), 1, '-');
		else
			rv = ft_makestr("inf", 3, 5);
	}
	else
		rv = ft_makestr("nan", 3, 5);
	return (rv);
}

t_string	*ft_calculat_d(long double num, t_string *vm, short e)
{
	t_string	*rv;

	rv = e > 0 ? long_pow(5, e) : long_pow(2, -e);
	rv = long_mult(rv, vm);
	if (e > 0)
	{
		if (rv->len >= (size_t)e + 1)
			vec_fast_pb(rv, '0', 1);
		else
			vec_fast_pb(rv, '0', e + 1 - rv->len);
		ft_memmove(rv->s + e + 1, rv->s + e, rv->len - e - 1);
		rv->s[e] = '.';
		if ((num > 0. && num < 1.) || (num < 0. && num > -1.))
			vec_fast_pb(rv, '0', 1);
	}
	else
	{
		rv = pushfront_v(rv, 2, '0');
		rv->s[1] = '.';
	}
	return (rv);
}

t_string	*ft_ftoa(long double num)
{
	t_string		*rv;
	t_string		*vm;
	short			e;
	unsigned long	m;

	take_exp(num, &e, &m);
	if (e == 32767)
		return (check_inf_nan(num));
	vm = ft_utoa(m);
	e = (short)16446 - e;
	if (!m)
	{
		vm = pushfront_v(vm, 2, '0');
		vm->s[1] = '.';
		return (!take_exp(num, &e, &m) ? pushfront_v(vm, 1, '-') : vm);
	}
	rv = ft_calculat_d(num, vm, e);
	if (num < 0.)
		vec_fast_pb(rv, '-', 1);
	rv->s = ft_strrev(rv->s);
	rv->cap = rv->len + 1;
	return (rv);
}
