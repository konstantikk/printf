/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 23:12:48 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/13 16:49:47 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pars_aposrophe(t_vap_data_t *node)
{
	if (!node->f_apostrophe)
		++(node->f_apostrophe);
	++(node->flags);
}

void		pars_dot(t_vap_data_t *node)
{
	if (!node->f_dot)
		++(node->f_dot);
	if (*(++(node->flags)) == '*')
	{
		pars_star(node);
		return ;
	}
	node->dot = ft_atoi(node->flags);
	while (ft_isdigit(*(node->flags)))
		++(node->flags);
}
