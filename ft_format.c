/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:54:57 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/13 17:10:37 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pars_h(t_vap_l *node)
{
	node->size_flags[0] += 1;
	++(node->flags);
}

void	pars_l(t_vap_l *node)
{
	node->size_flags[1] += 1;
	++(node->flags);
}

void	pars_z(t_vap_l *node)
{
	node->size_flags[1] += 2;
	++(node->flags);
}

void	pars_j(t_vap_l *node)
{
	node->size_flags[1] += 2;
	++(node->flags);
}

void	pars_ll(t_vap_l *node)
{
	node->size_flags[2] += 1;
	++(node->flags);
}
