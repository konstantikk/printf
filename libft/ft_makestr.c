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

t_string	*ft_makestr(const char *s, size_t len, size_t cap)
{
	t_string *str;

	if (len + 1 > cap)
		return (0);
	str = (t_string*)malloc(sizeof(t_string));
	if (!str)
		return (0);
	if (!(str->s = (char*)ft_memalloc(cap)))
		return (0);
	ft_memcpy(str->s, s, len);
	str->len = len;
	str->cap = cap;
	return (str);
}
