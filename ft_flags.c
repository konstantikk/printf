/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:46:19 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/08 12:30:57 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void            pars_hash(t_vap_data_t *node)
{
	if (!node->f_hash)
		++node->f_hash;
	++(node->flags);
}

void            pars_minus(t_vap_data_t *node)
{
	if (!(node->f_minus))
	{
		++node->f_minus;
		node->f_zero = 0;
	}
	++(node->flags);
}

void            pars_plus(t_vap_data_t *node)
{
	if (!(node->f_plus))
	{
		++node->f_plus;
		node->f_space = 0;
	}
	++(node->flags);
}

void            pars_zero(t_vap_data_t *node)// modif for type diouxX
{
	if (!node->f_zero && !node->f_minus)
		++(node->f_zero);
	++(node->flags);
}

 void            pars_space(t_vap_data_t *node)
{
	if (!(node->f_space) && !(node->f_plus))
		++(node->f_space);
	++(node->flags);
}
