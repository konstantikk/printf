/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pr_data_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 23:37:28 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/20 06:06:40 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		fpw_for_str(t_vap_l *node)
{
	char	*s;

	if (node->f_dot && node->dot < (int)node->pr_data->len && node->type == 's')
	{
		s = ft_strsub(node->pr_data->s, 0, node->dot);
		free(node->pr_data->s);
		node->pr_data->s = s;
		node->pr_data->len = node->dot;
		node->pr_data->cap = node->dot + 1;
	}
	if (!node->f_minus && (size_t)node->width > node->pr_data->len)
	{
		node->pr_data = pushfront_v(node->pr_data, node->width -
		node->pr_data->len, node->f_zero && node->type != 'f' ? '0' : ' ');
	}
	if (node->f_minus && (size_t)node->width > node->pr_data->len)
		vec_fast_pb(node->pr_data, ' ', node->width - node->pr_data->len);
}

void		pr_data_unsigned(t_vap_l *node)
{
	if ((node->size_flags)[1])
		node->pr_data = itoa_base(node->data->ul, node, 0);
	else if ((node->size_flags)[0])
		node->pr_data = itoa_base((node->size_flags)[0] % 2 ?
				node->data->uh : node->data->uc, node, 0);
	else
		node->pr_data = itoa_base(node->data->ui, node, 0);
}

void		pr_data_for_nbr(t_vap_l *node)
{
	int f;

	f = 0;
	if (node->type == 'i' || node->type == 'd' || node->type == 'b')
	{
		if ((node->size_flags)[1])
		{
			if (node->data->l < 0 && (node->data->l = -node->data->l))
				f = 1;
			node->pr_data = itoa_base(node->data->l, node, f);
		}
		else if ((node->size_flags)[0])
			node->pr_data = htoa((node->size_flags)[0] % 2
					? node->data->h : node->data->c, node);
		else
		{
			if (node->data->i < 0 && (node->data->ul =
					(unsigned long)-(long)node->data->i) && (f = 1))
				node->pr_data = itoa_base(node->data->ul, node, f);
			else
				node->pr_data = itoa_base(node->data->i, node, f);
		}
	}
	else
		pr_data_unsigned(node);
}
