/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:17:47 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 18:17:48 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_ctoi(char c)
{
	return (c - '0');
}

void	ft_put_series_fd(char c, size_t len, int fd)
{
	while (len)
	{
		write(fd, &c, 1);
		len--;
	}
}

void	ft_print_also_null(char *str, size_t len)
{
	size_t index;

	index = 0;
	while (index < len)
		ft_putchar_fd(str[index++], 1);
}
