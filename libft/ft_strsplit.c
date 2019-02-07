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

static size_t	ft_findc(const char *s, char c)
{
	size_t len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static size_t	ft_wordsn(const char *s, char c)
{
	size_t r;

	if (!*s)
		return (0);
	r = 0;
	while (*++s)
		if (*s == c && *s != *(s - 1))
			r++;
	return ((*(s - 1) == c) ? (r) : (++r));
}

static int		wdel(char ***words, int i)
{
	int j;

	j = 0;
	while (j < i)
		free((*words)[j++]);
	free(*words);
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**r;
	size_t	n;
	int		i;

	if (!s)
		return (0);
	i = 0;
	n = ft_wordsn(s, c);
	if (!(r = (char**)ft_memalloc((1 + n) * sizeof(char*))))
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (!(*r = (char*)ft_memalloc(ft_findc(s, c) + 1)) && wdel(&r, i))
			return (0);
		ft_strncpy(*r, s, ft_findc(s, c));
		r++;
		i++;
		s += ft_findc(s, c);
	}
	(*(s - 1) == c) ? (--r) : (r);
	*r = 0;
	return (r - n);
}
