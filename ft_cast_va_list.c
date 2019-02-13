/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_va_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:17:25 by jziemann          #+#    #+#             */
/*   Updated: 2019/02/13 17:20:50 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_float_cast(t_vap_data_t *node, va_list args)
{
	if ((node->size_flags)[2])
		node->data->lf = va_arg(args, long double);
	else
		node->data->f = va_arg(args, double);
}

void			ft_int_cast(t_vap_data_t *node, va_list args)
{
	if ((node->size_flags)[1])
		node->data->l = va_arg(args, long);
	else if ((node->size_flags)[0] % 2)
		node->data->h = va_arg(args, int);
	else if ((node->size_flags)[0])
		node->data->c = va_arg(args, int);
	else
		node->data->i = va_arg(args, int);
}

void			ft_unsigned_cast(t_vap_data_t *node, va_list args)
{
	if ((node->size_flags)[1])
		node->data->ul = va_arg(args, unsigned long);
	else if ((node->size_flags)[0] % 2)
		node->data->uh = va_arg(args, unsigned int);
	else if ((node->size_flags)[0])
		node->data->uc = va_arg(args, unsigned int);
	else
		node->data->ui = va_arg(args, unsigned int);
}

void			read_pr_va_list(t_vap_data_t *begin, va_list args) //TODO
{
	while (begin)
	{
		begin->data = (t_cast *)malloc(16);
		if (begin->type == 'f')
			ft_float_cast(begin, args);
		if (ft_strchr("id", begin->type))
			ft_int_cast(begin, args);
		if (ft_strchr("ouxX", begin->type))
			ft_unsigned_cast(begin, args);
		if (begin->type == 'c')
			begin->data->c = va_arg(args, int);
		if (begin->type == 's')
			begin->data->p = va_arg(args, char *);
		if (begin->type == 'p')
			begin->data->p = va_arg(args, void *);
		begin = begin->next;
	}
}
