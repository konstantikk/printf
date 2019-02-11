/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:49:31 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/11 19:23:04 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long		ft_dvigai_tochku(long double n, int dot, int *intlen)
{
	long	i;
	int 	f;
	int		len;

	i = 1;
	len = 0;
	f = n < 0 ? -1 : 1;
	n = n < 0 ? -n : n;
	while (i <= (long)n)
	{
		i *= 10;
		++len;
	}
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
	int 	len;
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
	while (i <= n)
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