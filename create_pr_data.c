/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:46:19 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/13 17:16:10 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			take_val(t_vap_l *begin, int i)
{
	while (begin->ind != i)
		begin = begin->next;
	return (begin->data->i);
}

void		create_pr_data_helper(t_vap_l *begin)
{
	if (begin->dot < 0)
	{
		begin->dot = begin->type == 'f' ? 6 : 0;
		begin->f_dot = 0;
	}
	if (begin->width < 0)
	{
		begin->width *= -1;
		begin->f_minus = 1;
	}
}

void		create_pr_data(t_vap_l *begin)
{
	t_vap_l	*node;

	node = begin;
	while (begin)
	{
		begin->dot = begin->dot < 0 ? take_val(node, -begin->dot) : begin->dot;
		begin->width = begin->width < 0 ? take_val(node, -begin->width)
		: begin->width;
		create_pr_data_helper(begin);
		if (begin->type == 'f')
			float_pr_data(begin);
		else if (begin->type && ft_strchr("idouxXpb", begin->type))
			int_pr_data(begin);
		else if (begin->type == 's')
			string_pr_data(begin);
		else if (begin->type == 'c')
			char_pr_data(begin);
		else
			trash_pr_data(begin);
		if (!(begin = begin->next))
			return ;
	}
}

void		spplus_mnpl(t_vap_l *node, t_string *vec, unsigned copy, int f)
{
	if ((copy == 0 || !f) && vec->s[vec->len - 1] != ' ')
	{
		if (node->f_space)
		{
			vec_fast_pb(vec, ' ', 1);
			node->f_space = 0;
		}
		if (node->f_plus)
		{
			vec_fast_pb(vec, '+', 1);
			node->f_plus = 0;
		}
	}
}
