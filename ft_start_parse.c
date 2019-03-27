/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 23:01:19 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/19 16:33:13 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*g_flags = "*#-+hlzjL'0.$ 123456789";

void			(*g_pars_fun[14])(t_vap_l *a) =
{
	pars_star,
	pars_hash,
	pars_minus,
	pars_plus,
	pars_h,
	pars_l,
	pars_z,
	pars_j,
	pars_ll,
	pars_aposrophe,
	pars_zero,
	pars_dot,
	pars_bax,
	pars_space
};

char			*ft_find_type(char *str)
{
	char	*itr;

	while (ft_strchr(FLAGS, *str))
	{
		if (!*str)
			return (str);
		if (*str == '$')
		{
			itr = str - 1;
			while (*itr == '0')
				--itr;
			if (!ft_isdigit(*itr) && *itr != '*')
				break ;
		}
		str++;
	}
	return (str);
}

t_vap_l			*ft_write_list_node(t_vap_l *n, char **str, char **itr, int *i)
{
	n->ind = (*i)++;
	n->start = *str;
	*itr = ft_find_type(++(*str));
	n->type = **itr;
	if (**itr == 'f')
		n->dot = 6;
	if (!(n->flags = ft_strsub(*str, 0, *itr - *str)))
		return (0);
	*str = **itr ? ++(*itr) : *itr;
	n->finish = *itr;
	return (n);
}

t_vap_l			*ft_make_vaplist(char *str)
{
	t_vap_l			*b;
	t_vap_l			*node;
	char			*itr;
	int				i;

	i = 1;
	if (!(b = (t_vap_l *)ft_memalloc(sizeof(t_vap_l))) || !ft_strchr(str, '%'))
		return (free_vap_list(b));
	node = b;
	while (*str)
	{
		if (!(str = ft_strchr(str, '%')))
			return (b);
		if (!(ft_write_list_node(node, &str, &itr, &i)))
			return (free_vap_list(b));
		if (ft_strchr(itr, '%'))
		{
			if (!(node->next = (t_vap_l *)ft_memalloc(sizeof(t_vap_l))))
				return (free_vap_list(b));
		}
		else
			node->next = 0;
		node = node->next;
	}
	return (b);
}

void			check_bax(t_vap_l *node)
{
	int	size_flags[3];
	int	ind;

	if (node->bax > node->ind)
	{
		ind = node->bax;
		size_flags[0] = (node->size_flags)[0];
		size_flags[1] = (node->size_flags)[1];
		size_flags[2] = (node->size_flags)[2];
		while (ind != node->ind)
			node = node->next;
		(node->size_flags)[0] = size_flags[0];
		(node->size_flags)[1] = size_flags[1];
		(node->size_flags)[2] = size_flags[2];
	}
}

void			pars_flags(t_vap_l *begin)
{
	char	*flags;
	char	f;

	while (begin)
	{
		flags = begin->flags;
		while (begin->flags && *(begin->flags))
			if (ft_isdigit(*(begin->flags)) && *(begin->flags) != '0')
				pars_bax(begin);
			else
			{
				f = *(begin->flags);
				g_pars_fun[ft_strchr(FLAGS, *(begin->flags)) - FLAGS](begin);
				if ((f == '*' || f == '.') && begin->f_star)
					begin = begin->next;
			}
		if (ft_strchr(flags, '$'))
			check_bax(begin);
		free(flags);
		begin->flags = 0;
		begin = begin->next;
	}
}
