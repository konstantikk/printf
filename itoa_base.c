/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:49:31 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/16 21:19:12 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_base(char type)
{
	if (ft_strchr("diu", type))
		return (10);
	else if (type == 'x' || type == 'X')
		return (16);
	else if (type == 'b')
		return (2);
	else
		return (8);
}

static int	count_digits(unsigned long n, int base)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / base;
		++count;
	}
	return (count);
}

t_vector	*itoa_base(unsigned long n, char type, int f)
{
	int		base;
	char	l;
	t_vector	*vec;

	base = find_base(type);
	vec =  makevec();
	if (base == 2 && f)
		n =	(~n) + 1;
	if (!n)
		pushbackvec(vec, '0');
	l = (char)(type == 'x' ? 'a' : 'A');
	while (n)
	{
		pushbackvec(vec, (char)(n % base < 10 ? n % base + '0' : n % base % 10 + l));
		n = n / base;
	}
	if (f)
		pushbackvec(vec,'-');
	ft_strrev(vec->v);
	return (vec);
}

void		pr_data_for_nbr(t_vap_data_t *node)
{
	int f;

	f = 0;
	if (node->type == 'i' || node->type == 'd' || node->type == 'b')
	{
		if ((node->size_flags)[1])
		{
			if (node->data->l < 0 && (node->data->l = -node->data->l))
				f = 1;
			node->pr_data = itoa_base(node->data->l, node->type, f);
		}
		else if ((node->size_flags)[0])
		{
			if ((node->size_flags)[0] % 2 && node->data->c < 0 && (node->data->c = -node->data->c))
				f = 1;
			else if (node->data->h < 0 && (node->data->h = -node->data->h))
				f = 1;
			node->pr_data = itoa_base((node->size_flags)[0] % 2 ? node->data->h : node->data->c, node->type, f);
		}
		else
		{
			if (node->data->i < 0 && (node->data->i = -node->data->i))
				f = 1;
			node->pr_data = itoa_base(node->data->i, node->type, f);
		}
	}
	else
	{
		if ((node->size_flags)[1])
			node->pr_data = itoa_base(node->data->ul, node->type, f);
		else if ((node->size_flags)[0])
			node->pr_data = itoa_base((node->size_flags)[0] % 2 ? node->data->uh : node->data->uc, node->type, f);
		else
			node->pr_data = itoa_base(node->data->ui, node->type, f);
	}
}
