/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:46:52 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/02/13 16:54:11 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			create_bax_nod(t_vap_data_t **node)
{
	int i;

	i = (*node)->ind + 1;
	(*node)->next = (t_vap_data_t *)ft_memalloc(sizeof(t_vap_data_t));
	*node = (*node)->next;
	(*node)->type = 'd';
	(*node)->flags = ft_strnew(0);
	(*node)->ind = i;
	(*node)->f_star++;
}

void			bax_indexator(t_vap_data_t *node, int i)
{
	node->bax = i;
	if (!(node = node->next))
		return ;
	while (node->bax == 0)
	{
		if (!node->f_star)
			node->bax = ++i;
		if (!(node->next))
		{
			while (node->ind < i)
			{
				create_bax_nod(&node);
				if (!(node = node->next))
					return ;
			}
		}
		else
			node = node->next;
	}
}

void			pars_bax(t_vap_data_t *node)
{
	int		n;
	int		size_flags[3];
	char	type;

	type = node->type;
	n = ft_atoi(node->flags);
	while (ft_isdigit(*(node->flags)))
		++(node->flags);
	if (*(node->flags) == '$')
	{
		bax_indexator(node, n);
		++(node->flags);
		while (node->ind < n)
		{
			if (node->next)
				node = node->next;
			else
				create_bax_nod(&node);
		}
		if (!node->f_star)
			node->type = type;
	}
	else
		node->width = n;
}

void			create_star_nod(t_vap_data_t *node, int n)
{
	t_vap_data_t *nextnode;

	if (!n)
	{
		nextnode = node->next;
		node->next = (t_vap_data_t *)malloc(sizeof(t_vap_data_t));
		ft_memcpy(node->next, node, sizeof(t_vap_data_t));
		node->next->next = nextnode;
		node->f_star = 1;
		node->type = 'd';
		if (*(node->flags - 2) != '.')
			node->next->width = -node->ind;
		else
			node->next->dot = -node->ind;
		node->flags = ft_strnew(0);
		while ((node = node->next))
			++(node->ind);
		return ;
	}
	while (node->ind < n)
	{
		if (node->next)
			node = node->next;
		else
			create_bax_nod(&node);
	}
}

void			pars_star(t_vap_data_t *node)
{
	int i;
	int ind;

	i = 0;
	ind = ft_atoi(++(node->flags));
	if (ind == 0)
	{
		if (ft_isdigit(*node->flags))
		{
			while ((node->flags)[i] == '0')
				++i;
			if (*node->flags == '$')
				node->flags += i + 1;
		}
		else
			create_star_nod(node, ind);
	}
	else
	{
		while (ft_isdigit((node->flags)[i]))
			++i;
		if ((node->flags)[i] != '$')
		{
			create_star_nod(node, 0);
			return ;
		}
		if (*(node->flags - 2) != '.')
			node->width = -ind;
		else
			node->dot = -ind;
		node->flags += i + 1;
		create_star_nod(node, ind);
	}
}
