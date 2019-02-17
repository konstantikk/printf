/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_fpw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 23:37:28 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/17 05:49:51 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		fpw_for_integer(t_vap_data_t *node) // # space +  - 0 and widht   dot  for all types|||
{
	if (node->f_zero && node->f_dot)///ignore zero
		++node->f_zero;
	if ((node->pr_data)->v[0] != '-' && node->type == 'd' && node->type == 'i')/// for tupe i  and d
	{
		if (node->f_space)
			node->pr_data = pushfront_v(node->pr_data, 1, ' ');
		if (node->f_plus)
			node->pr_data = pushfront_v(node->pr_data, 1, '+');
	}
	if (node->dot > (node->pr_data)->len)
		node->pr_data = pushfront_v(node->pr_data, node->dot - (node->pr_data)->len, '0');
	if (node->width > (node->pr_data)->len)      ///width
	{
		if (node->f_minus)
			while ((node->pr_data)->len != node->width)
				pushbackvec(node->pr_data, ' ');
		else
		{
			if (node->f_zero)
				node->pr_data = pushfront_v(node->pr_data, node->width - (node->pr_data)->len, '0');
			else
			{
				if (node->f_hash && (node->type == 'o' || node->type == 'u'))
				{
					node->pr_data = pushfront_v(node->pr_data, 1, '0');
					node->f_hash++;
				}
				else if (node->f_hash && (node->type == 'x' || node->type == 'X' || node->type == 'b'))
				{
					node->pr_data = pushfront_v(node->pr_data, 1, node->type);
					node->pr_data = pushfront_v(node->pr_data, 1, '0');
					node->f_hash++;
				}
				node->pr_data = pushfront_v(node->pr_data, node->width - (node->pr_data)->len, ' ');
			}
		}
	}
	if (node->f_hash && (node->type == 'o' || node->type == 'u'))
		node->pr_data = pushfront_v(node->pr_data, 1, '0');
	if (node->f_hash && (node->type == 'x' || node->type == 'X' || node->type == 'b'))
	{
		node->pr_data = pushfront_v(node->pr_data, 1, node->type);
		node->pr_data = pushfront_v(node->pr_data, 1, '0');
	}
}

void		fpw_for_str(t_vap_data_t *node)
{
	size_t	len;
	char	*s;
	
	len = ft_strlen(node->pr_data->v);
	if (node->f_dot && node->dot < (int) len && node->type == 's')
	{
		s = ft_strsub(node->pr_data->v, 0, node->dot);
		free(node->pr_data->v);
		node->pr_data->v = s;
		node->pr_data->len = node->dot;
	}
	if (!node->f_minus && node->width > node->pr_data->len)
		node->pr_data = pushfront_v(node->pr_data, node->width - node->pr_data->len, node->f_zero ? '0' : ' ');
	if (node->f_minus && node->width > node->pr_data->len)
		while (node->pr_data->len != node->width)
			pushbackvec(node->pr_data, ' ');

}
