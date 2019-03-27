/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:46:52 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/03/12 22:41:01 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		vec_fast_pb(t_string *str, char c, size_t n)
{
	char		*news;

	if (!str)
		return ;
	if (str->len + n >= str->cap)
	{
		while (str->len + n >= str->cap)
			str->cap *= 2;
		news = ft_memalloc(str->cap);
		ft_memcpy(news, str->s, str->len);
		while (n--)
			news[str->len++] = c;
		free(str->s);
		str->s = news;
	}
	else
	{
		while (n--)
			str->s[str->len++] = c;
		str->s[str->len] = 0;
	}
}

char		*ft_strrev(char *str)
{
	char	*r;
	size_t	i;
	size_t	len;

	if (!str)
		return (0);
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

t_string	*makevec(void)
{
	t_string	*r;

	if (!(r = (t_string *)malloc(sizeof(t_string))))
		return (0);
	r->cap = 10;
	r->len = 0;
	if (!(r->s = ft_memalloc(11)))
		return (0);
	return (r);
}

t_string	*pushfront_v(t_string *v, size_t n, char c)
{
	t_string	*rv;

	rv = (t_string *)malloc(sizeof(t_string));
	rv->cap = v->cap + n;
	rv->len = 0;
	rv->s = ft_memalloc(rv->cap);
	vec_fast_pb(rv, c, n);
	ft_memcpy(rv->s + n, v->s, v->len);
	rv->len += v->len;
	free_vec(&v);
	return (rv);
}

void		free_vec(t_string **v)
{
	if (*v && (*v)->s)
	{
		free((*v)->s);
		(*v)->s = 0;
	}
	if (*v)
	{
		free(*v);
		*v = 0;
	}
}
