/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:13:06 by ppunzo            #+#    #+#             */
/*   Updated: 2021/01/17 11:13:08 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *res;

	if (!l)
		return (0);
	res = 0;
	while (l)
	{
		new = ft_lstnew(f(l->content));
		if (!new)
		{
			ft_lstclear(&res, del);
			return (0);
		}
		ft_lstadd_back(&res, new);
		l = l->next;
	}
	return (res);
}
