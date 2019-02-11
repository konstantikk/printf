/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 23:01:19 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/08 12:29:48 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char            *g_flags = "*#-+hlzjL'0.$ 123456789";

void            (*pars_fun[14])(t_vap_data_t *a) =
{
	pars_star,
	pars_hash,
	pars_minus,
	pars_plus,
	pars_h,
	pars_l,
	pars_z,
	pars_j,
	pars_L,
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

		if (*str == '$')
		{
			itr = str - 1;
			while (*itr == '0')
				--itr;
			if (!ft_isdigit(*itr) && *itr != '*')
				break;
		}
		str++;
	}
	return (str);
}

t_vap_data_t    *ft_make_vaplist(char *str)
{
	t_vap_data_t    *begin;
	t_vap_data_t    *node;
	char            *itr;
	int             i;

	i = 1;
	begin = (t_vap_data_t *)ft_memalloc(sizeof(t_vap_data_t));  //TODO
	node = begin;
	while (*str)
	{
		if (!(str = ft_strchr(str, '%')))
			return (begin); // TODO ft_free
		node->ind = i++;
		node->start = str;
		itr = ft_find_type(++str); 
		node->type = *itr;
		if (*itr == 'f')
			node->dot = 6;
		node->flags = ft_strsub(str, 0, itr++ - str); // TODO
		str = itr;
		node->finish = itr;
		if (ft_strchr(itr, '%'))
			node->next = (t_vap_data_t *)ft_memalloc(sizeof(t_vap_data_t)); //TODO
		else
			node->next = 0;
		node = node->next;
	}
	return(begin);
}

 void            check_bax(t_vap_data_t *node)
{
	int size_flags[3];
	int ind;

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

void            pars_flags(t_vap_data_t *begin)
{
	char    *flags;
	char    f;

	while (begin)
	{
		flags = begin->flags;
		while (*(begin->flags))
			if (ft_isdigit(*(begin->flags)) && *(begin->flags) != '0')
			{
				pars_bax(begin);
			}
			else
			{
				f = *(begin->flags);
				pars_fun[ft_strchr(FLAGS, *(begin->flags)) - FLAGS](begin);
				if ((f == '*' || f == '.') && begin->f_star)
					begin = begin->next;
			}
		if (ft_strchr(flags, '$'))
			check_bax(begin);
		free(flags);
		begin = begin->next;
	}
}
