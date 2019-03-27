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

t_vap_l		*free_vap_list(t_vap_l *begin)
{
	t_vap_l	*prev_node;

	prev_node = begin;
	while (begin)
	{
		free(begin->data);
		if (begin->flags)
		{
			free(begin->flags);
			begin->flags = 0;
		}
		free_vec(&(begin->pr_data));
		begin = begin->next;
		free(prev_node);
		prev_node = begin;
	}
	return (0);
}

int			ft_printprintf(t_vap_l *begin, char *format)
{
	int		rd;
	t_vap_l	*node;

	rd = 0;
	node = begin;
	while (begin)
	{
		if (!begin->f_star)
		{
			rd += write(1, format, begin->start - format);
			rd += write(1, begin->pr_data->s, begin->pr_data->len);
			format = begin->finish;
		}
		begin = begin->next;
	}
	rd += write(1, format, ft_strchr(format, 0) - format);
	free_vap_list(node);
	return (rd);
}

int			ft_printf(char *format, ...)
{
	t_vap_l	*begin;
	va_list	args;

	pars_flags((begin = ft_make_vaplist(format)));
	va_start(args, format);
	read_pr_va_list(begin, args);
	va_end(args);
	create_pr_data(begin);
	return (ft_printprintf(begin, format));
}
