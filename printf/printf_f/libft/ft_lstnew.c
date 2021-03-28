/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:38:40 by ppunzo            #+#    #+#             */
/*   Updated: 2021/01/17 10:38:41 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new;

	new = (t_list*)malloc(1 * sizeof(t_list*));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}
