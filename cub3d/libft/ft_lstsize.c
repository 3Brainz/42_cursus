/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:11:34 by ppunzo            #+#    #+#             */
/*   Updated: 2021/01/17 11:11:36 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*nxt;

	len = 0;
	nxt = lst;
	while (nxt)
	{
		len++;
		nxt = nxt->next;
	}
	return (len);
}