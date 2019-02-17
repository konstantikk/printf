/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:49:31 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/17 05:44:18 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
char	*ft_strrev(char *str)
{
	char	*r;
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	r = ft_strnew(len);
	i = 0;
	while (str[i])
	{
		r[i] = str[len - 1 - i];
		++i;
	}
	ft_memcpy(str, r, len);
	free(r);
	return (str);
}

t_vector	*makevec(void)
{
	t_vector	*r;

	if (!(r = (t_vector *)malloc(sizeof(t_vector))))
		return (0);
	r->cap = 10;
	r->len = 0;
	if (!(r->v = ft_memalloc(11)))
		return (0);
	return (r);
}

void		pushbackvec(t_vector *v, char c)
{
	char	*str;

	if (v->cap == v->len)
	{
		v->cap *= 2;
		if (!(str = ft_memalloc(v->cap + 1)))
			return ;
		ft_memcpy(str, v->v, v->len);
		free(v->v);
		v->v = str;
	}
	v->v[(v->len)++] = c;
}

void		l_mul(t_vector *v, char c)
{
	char *str;
	char next_r;

	str = v->v;
	next_r = 0;
	c = c - '0';
	while (*str || next_r)
	{
		if (!*str)
		{
			pushbackvec(v, next_r % (char)10 + (char)'0');
			next_r /= 10;
			str = v->v + v->len;
			continue ;
		}
		*str = (*str - (char)'0') * c + next_r;
		next_r = *str / (char)10;
		*str = *str % (char)10 + (char)'0';
		++str;
	}
}

t_vector	*long_pow(short digit, long power)
{
	t_vector	*r;

	r = makevec();
	digit += '0';
	pushbackvec(r, (char)digit);
	while (--power)
		l_mul(r, (char)digit);
	return (r);
}

t_vector	*long_sum(t_vector *n1, t_vector *n2)
{
	char		carry;
	t_vector	*rv;
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
	while(i < n1->len)
	{
		carry += n1->v[i] - '0' + (i < n2->len ? n2->v[i] - '0' : 0);
		pushbackvec(rv, carry % 10 + '0');
		carry /= 10;
		++i;
	}
	if (carry)
		pushbackvec(rv, carry % 10 + '0');
	free(n1->v);
	free(n2->v);
	free(n1);
	free(n2);
	return (rv);
}

t_vector	*pushfront_v(t_vector *v, size_t n, char c)
{
	int			i;
	t_vector	*rv;

	rv = (t_vector *)malloc(sizeof(t_vector));
	rv->cap = v->cap + n;
	rv->len = 0;
	rv->v = ft_memalloc(rv->cap);
	i = 0;
	while (i < n)
	{
		pushbackvec(rv, c);
		++i;
	}
	ft_memcpy(rv->v + i, v->v, v->len);
	rv->len += v->len;
	return (rv);
}

t_vector	*long_mult(t_vector *v1, t_vector *v2)
{
	size_t		i;
	t_vector	*rv;
	t_vector	*hv;

	if (v2->len > v1->len)
	{
		rv = v1;
		v1 = v2;
		v2 = rv;
	}
	rv = makevec();
	pushbackvec(rv, '0');
	i = 0;
	while(i < v2->len)
	{
		hv = (t_vector *)malloc(sizeof(t_vector));
		hv->len = v1->len;
		hv->cap = v1->cap;
		hv->v = ft_strnew(hv->cap);
		ft_memcpy(hv->v, v1->v, v1->cap);
		l_mul(hv, v2->v[i]);
		hv = pushfront_v(hv, i, '0');
		rv = long_sum(rv, hv);
		i++;
	}
	return (rv);
}

int			take_exp(long double n, short *e, long *m)
{
	int			i;
	t_ld		f;

	f.fn = n;
	*e = f.hn[4] & (short)32767;
	*m = f.ln;
	i = f.hn[4] == *e;
	return (i);
}

t_vector	*ft_ftoa(long double num)
{
	t_vector 	*rv;
	t_vector 	*vm;
	short		e;
	long		m;

	take_exp(num, &e, &m);
	vm = (t_vector *)malloc(sizeof(t_vector));
	vm->v = ft_strrev(itoa_base(m, 'd', 0)->v);
	vm->len = ft_strlen(vm->v);
	vm->cap = vm->len;
	e = (short)16446 - e;
	if (!m)
	{
		vm = pushfront_v(vm, 2, '0');
		vm->v[1] = '.';
		return (!take_exp(num, &e, &m) ? pushfront_v(vm, 1, '-') : vm);
	}
	rv = e > 0 ? long_pow(5, e) : long_pow(2, -e);
	rv = long_mult(rv, vm);
	if (e > 0)
	{
		pushbackvec(rv, 0);
		ft_memmove(rv->v + e + 1, rv->v + e, rv->len - e - 1);
		rv->v[e] = '.';
		if ((num > 0. && num < 1.) || (num < 0. && num > -1.))
			pushbackvec(rv, '0');
	}
	else
	{
		rv = pushfront_v(rv, 2, '0');
		rv->v[1] = '.';
	}
	if (num < 0.)
		pushbackvec(rv, '-');
	rv->v = ft_strrev(rv->v);
	return (rv);
}
