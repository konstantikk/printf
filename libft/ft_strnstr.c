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

static int		strisnstr(const char *str, const char *to_find, size_t len)
{
	int i;

	i = 0;
	while (to_find[i])
	{
		if (str[i] != to_find[i])
			return (0);
		++i;
		if (!--len && to_find[i])
			return (0);
	}
	return (1);
}

char			*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	int i;

	if (*to_find == '\0')
		return ((char*)str);
	i = 0;
	while (str[i] != '\0' && len)
	{
		if (str[i] == to_find[0])
		{
			if (strisnstr(str + i, to_find, len))
				return ((char*)str + i);
		}
		len--;
		i++;
	}
	return (0);
}
