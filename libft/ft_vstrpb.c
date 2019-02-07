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

void	ft_vstrpb(t_string *str, char *s, size_t len)
{
	char		*news;

	if (!str || !s)
		return ;
	if (str->len + len + 1 < str->cap)
	{
		ft_memmove(str->s + str->len, s, len);
		str->len += len;
	}
	else
	{
		while (str->len + len + 1 >= str->cap)
			str->cap *= 2;
		if (!(news = (char*)malloc(str->cap)))
			return ;
		ft_memmove(news, str->s, str->len);
		ft_memmove(news + str->len, s, len);
		if (!(str->s = (char*)ft_memalloc(str->cap)))
			return ;
		str->len += len;
		ft_memmove(str->s, news, str->len);
		free(news);
	}
}
