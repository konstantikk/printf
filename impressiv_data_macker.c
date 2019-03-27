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

void	float_pr_data(t_vap_l *node)
{
	if (node->size_flags[2])
		node->pr_data = ft_ftoa(node->data->lf);
	else
		node->pr_data = ft_ftoa(node->data->f);
	if (ft_isdigit(node->pr_data->s[0]) || node->pr_data->s[0] == '-')
		pars_float_pr_data(node);
	else
		fpw_for_str(node);
}

void	int_pr_data(t_vap_l *node)
{
	if (node->type == 'p' && ++(node->size_flags[1]))
		++node->f_hash;
	if (!node->f_star)
		pr_data_for_nbr(node);
}

void	string_pr_data(t_vap_l *node)
{
	if (node->data->p)
		node->pr_data = ft_makestr((char *)node->data->p,
						ft_strlen((char *)node->data->p),
						ft_strlen((char *)node->data->p) + 1);
	else
		node->pr_data = ft_makestr("(null)", 6, 7);
	fpw_for_str(node);
}

void	char_pr_data(t_vap_l *node)
{
	node->pr_data = makevec();
	vec_fast_pb(node->pr_data, node->data->c, 1);
	fpw_for_str(node);
}

void	trash_pr_data(t_vap_l *node)
{
	node->pr_data = makevec();
	if (node->type || *(node->finish))
	{
		vec_fast_pb(node->pr_data, node->type, 1);
		fpw_for_str(node);
	}
}
