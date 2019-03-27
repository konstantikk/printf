/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:46:52 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/02/19 21:40:04 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		strange_five(t_string **num, char *j)
{
	char	*i;

	i = j;
	if (*i == '5')
	{
		while (*++i == '0')
			;
		*(--j) += *i || (!*i && ((*(j - 1) - '0') % 2)) ? 1 : 0;
	}
	else if (*j > '5')
		*(--j) += 1;
	while (*j == ':' || *j == '/')
	{
		if (*j == '/')
			*(j) = '.';
		else
			*j-- = '0';
		if (*j == '.')
			--j;
		*j += 1;
		if (j == (*num)->s)
			break ;
	}
}

void		round_float(t_string **num, int dot)
{
	char	*j;

	j = ft_strchr((*num)->s, '.') + dot + 1;
	if (j - (*num)->s > (long)(*num)->len)
		vec_fast_pb(*num, '0', j - (*num)->s - (*num)->len);
	else
	{
		strange_five(num, j);
		(*num)->s[0] == ':' && ((*num)->s[0] = '1');
		if ((*num)->s[0] == '.' && ((*num)->s[0] = '1'))
			*num = pushfront_v(*num, 1, '-');
	}
	*(ft_strchr((*num)->s, '.') + dot + 1) = 0;
	(*num)->len = ft_strlen((*num)->s);
}

int			help_float_pars(t_vap_l *node)
{
	if (ft_isdigit(node->pr_data->s[node->pr_data->len - 1]))
		round_float(&(node->pr_data), node->dot);
	if (!node->dot)
		node->pr_data->s[--(node->pr_data->len)] = 0;
	if (node->pr_data->s[0] != '-' && (node->f_plus || node->f_space))
		node->pr_data = pushfront_v(node->pr_data, 1, node->f_plus ? '+' : ' ');
	return (1);
}

void		pars_float_pr_data(t_vap_l *node)
{
	char	c;

	if (help_float_pars(node) && PRV->len < (size_t)node->width)
	{
		if (!node->f_minus)
		{
			if (node->f_zero)
			{
				if (ft_strchr("-+ ", PRV->s[0]))
				{
					c = PRV->s[0];
					PRV->s[0] = '0';
					PRV = pushfront_v(PRV, node->width - PRV->len - 1, '0');
					PRV = pushfront_v(PRV, 1, c);
				}
				else
					PRV = pushfront_v(PRV, node->width - PRV->len, '0');
			}
			else
				PRV = pushfront_v(PRV, node->width - PRV->len, ' ');
		}
		else
			vec_fast_pb(PRV, ' ', node->width - PRV->len);
	}
}

void		pars_star(t_vap_l *node)
{
	int i;
	int ind;

	i = 0;
	ind = ft_atoi(++(node->flags));
	if (ind == 0)
		help_pars_star(node, ind);
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
