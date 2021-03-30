/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 08:29:41 by ppunzo            #+#    #+#             */
/*   Updated: 2021/01/12 08:29:42 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	t_uc *a;

	a = (t_uc*)b;
	while (len != 0)
	{
		*a = (t_uc)c;
		a++;
		len--;
	}
	return (b);
}