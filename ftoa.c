/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:49:31 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/13 18:04:24 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long		ft_dvigai_tochku(long double n, int dot, int *intlen)
{
	long	i;
	int		f;
	int		len;

	i = 1;
	len = 0;
	f = n < 0 ? -1 : 1;
	n = n < 0 ? -n : n;
	if ((n < 0. && (long)n < 0) || (n > 0. && (long)n > 0))
	{
		while (i <= (long) n)
		{
			i *= 10;
			++len;
		}
	}
	else
		len = 18;
	*intlen = len;
	while (dot-- && len < 16)
	{
		n *= 10;
		++len;
	}
	(n - (long)n > 0.5 ? 1 : 0);
	if (len == 16)
		return (((n - (long)n > 0.4 ? 1 : 0) + (long)n) * f);
	return (((n - (long)n > 0.4 ? 1 : 0) + (long)n) * f);
}

char		*ftoa(long n, int dot, int intlen)
{
	int		len;
	int		f;
	long	i;
	char	*str;

	f = n < 0 ? 1 : 0;
	n = f ? -n : n;
	len = intlen + dot + (dot ? 1 : 0) + f;
	str = ft_strnew((size_t)(unsigned)len);
	ft_memset(str, '0', (size_t)(unsigned)len);
	i = 1;
	len = 0;
	while (i <= n && len < 18)
	{
		i *= 10;
		++len;
	}
	f ? *str++ = '-' : 0;
	while (len + 1)
	{
		if (len == intlen)
			str[len--] = '.';
		str[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (f ? str - 1 : str);
}

t_vector	*makevec(void)
{
	t_vector	*r;

	r = (t_vector *)malloc(sizeof(t_vector));
	r->cap = 10;
	r->len = 0;
	r->v = ft_memalloc(11);
	return (r);
}

void		pushbackvec(t_vector *v, char c)
{
	char	*str;

	if (v->cap == v->len)
	{
		v->cap *= 2;
		str = ft_memalloc(v->cap + 1);
		ft_memcpy(str, v->v, v->len);
		free(v->v);
		v->v = str;
	}
	v->v[(v->len)++] = c;
}

void		long_mul(t_vector *v, char c)
{
	char *str;
	char next_r;

	str = v->v;
	next_r = 0;
	while (*str || next_r)
	{
		if (!*str)
		{
			pushbackvec(v, next_r % (char)10 + (char)'0');
			next_r /= 10;
			str = v->v + v->len;
			continue ;
		}
		*str = (*str - (char)'0') * (c - (char)'0') + next_r;
		next_r = *str / (char)10;
		*str = *str % (char)10 + (char)'0';
		++str;
	}
}

t_vector	*long_pow(char digit, long power)
{
	int			i;
	t_vector	*r;

	r = makevec();
	pushbackvec(r, digit);
	while (--power)
		long_mul(r, digit);
	return (r);
}
/*
typedef union	u_Ld
{
	long double	fn;
	__int128_t	in;
}				t_Ld;

char		*ftoa(long double num)
{
	t_Ld	n;

	n.fn = num;

}
*//*
#include <stdio.h>
#include <string.h>
int main()
{
	t_vector *test;
	test = long_pow(2, 10);
	printf("%s", test->v);
}*/
