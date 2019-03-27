/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_manipulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:58:06 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/20 05:42:23 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		hash_mnpl(t_vap_l *node, t_string *vec, unsigned copy)
{
	if ((node->f_hash && (copy != 0 || node->type == 'o')) || node->type == 'p')
	{
		if (node->type == 'o' && !((copy == 0 && node->dot) ||
			vec->s[vec->len - 1] == '0'))
			vec_fast_pb(vec, '0', 1);
		else if (node->type == 'x' || node->type == 'X' || node->type == 'b' ||
				(node->type == 'p' && (node->type = 'x')))
		{
			vec_fast_pb(vec, node->type, 1);
			vec_fast_pb(vec, '0', 1);
		}
	}
}

void		minus_mnpl(t_vap_l *node, t_string *vec, unsigned copy, int f)
{
	if (vec->len < (size_t)node->width)
	{
		hash_mnpl(node, vec, copy);
		ft_strrev(vec->s);
		vec->cap = vec->len + 1;
		if ((node->f_space || node->f_plus) && (copy == 0 || !f))
		{
			if ((size_t)node->width - 1 > vec->len)
				vec_fast_pb(vec, ' ', node->width - 1 - vec->len);
		}
		else
		{
			if ((size_t)node->width > vec->len)
				vec_fast_pb(vec, ' ', node->width - vec->len);
		}
		ft_strrev(vec->s);
		vec->cap = vec->len + 1;
	}
}

void		zero_mnpl_hesh(t_vap_l *n, t_string *vec, unsigned copy)
{
	if (n->type == 'x' || n->type == 'X' || n->type == 'b')
	{
		if ((size_t)n->width - 2 > vec->len)
			vec_fast_pb(vec, '0', n->width - 2 - vec->len);
	}
	else
	{
		if ((size_t)n->width > vec->len)
			vec_fast_pb(vec, '0', n->width - vec->len);
	}
	hash_mnpl(n, vec, copy);
}

void		zero_mnpl(t_vap_l *n, t_string *vec, unsigned copy, int f)
{
	if (n->f_hash && copy != 0)
		zero_mnpl_hesh(n, vec, copy);
	else if (!n->f_hash || (n->f_hash && copy == 0))
	{
		if (f || ((n->f_space || n->f_plus) && copy == 0))
		{
			if ((size_t)n->width - 1 > vec->len)
				vec_fast_pb(vec, '0', n->width - 1 - vec->len);
		}
		else
		{
			if ((size_t)n->width > vec->len)
				vec_fast_pb(vec, '0', n->width - vec->len - (n->f_space
							|| n->f_plus ? 1 : 0));
		}
	}
	if (f)
		vec_fast_pb(vec, '-', 1);
}

void		width_mnpl(t_vap_l *node, t_string *vec, unsigned copy, int f)
{
	if (node->f_minus)
	{
		if (f)
			vec_fast_pb(vec, '-', 1);
		minus_mnpl(node, vec, copy, f);
	}
	else
	{
		if (!node->f_zero)
		{
			if (node->type == 'i' || node->type == 'd')
				spplus_mnpl(node, vec, copy, f);
			if (f)
				vec_fast_pb(vec, '-', 1);
			hash_mnpl(node, vec, copy);
			if ((size_t)node->width > vec->len)
				vec_fast_pb(vec, ' ', node->width - vec->len);
		}
		else
			zero_mnpl(node, vec, copy, f);
	}
}
