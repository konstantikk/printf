/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:39:20 by bmiklaz           #+#    #+#             */
/*   Updated: 2018/11/21 22:40:18 by bmiklaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		tens;
	int		k;

	k = (n < 0) ? -1 : 1;
	tens = 1;
	while ((n / tens <= -10 || n / tens >= 10) && (tens *= 10))
		k = (n < 0) ? -1 : 1;
	if (n < 0)
		write(fd, "-", 1);
	while (tens)
	{
		ft_putchar_fd((n / tens) * k + '0', fd);
		n %= tens;
		tens /= 10;
	}
}
