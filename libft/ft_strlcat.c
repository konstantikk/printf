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

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t r;

	r = ft_strlen(src);
	while (*dest++ && size)
	{
		size--;
		r++;
	}
	if (size == 0)
		return (r);
	while ((size-- - 1) && *src)
	{
		*(dest - 1) = *src++;
		dest++;
	}
	*(dest - 1) = '\0';
	return (r);
}
