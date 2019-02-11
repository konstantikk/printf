/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:49:31 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/11 19:23:04 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_base(char type)
{
	if (ft_strchr("diu", type))
		return (10);
	else if (type == 'x' || type == 'X')
		return (16);
	else
		return (8);
}

static int	count_digits(long long n, int base)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / base;
		++count;
	}
	return (count);
}

char		*itoa_base(long long n, char type)
{
	char	*str;
	int		base;
	size_t	len;
	char	l;

	base = find_base(type);
	len = (size_t)count_digits(n, base);
	str = (n < 0) ? ft_strnew(len + 1) : ft_strnew(len);
	if (!n)
		str[0] = '0';
	if (!str)
		return (NULL);
	l = (char)(type == 'x' ? 'a' : 'A');
	if (n < 0 && (n = -n))
		if ((type == 'd' || type == 'i') && (str[0] = '-'))
			len++;
	while (n)
	{
		str[--len] = (char)(n % base < 10 ? n % base + '0' : n % base % 10 + l);
		n = n / base;
	}
	return (str);
}
