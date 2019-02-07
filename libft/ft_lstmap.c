/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:39:20 by bmiklaz           #+#    #+#             */
/*   Updated: 2018/11/21 22:40:18 by bmiklaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_del(void *a, size_t t)
{
	ft_memdel(&a);
	t = 0;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*start;
	t_list	*iter;

	if (!lst || !f)
		return (0);
	start = f(lst);
	if (!start)
		return (0);
	iter = start;
	while (lst->next)
	{
		lst = lst->next;
		if (!(iter->next = f(lst)))
		{
			ft_lstdel(&start, &ft_del);
			return (0);
		}
		iter = iter->next;
	}
	iter = 0;
	return (start);
}
