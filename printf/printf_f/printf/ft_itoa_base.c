/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:16:14 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 18:16:15 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static size_t	ft_num_size(size_t num, size_t charset_len)
{
	long int	divider;
	size_t		len;

	len = 0;
	divider = 1;
	if (num == 0)
		return (1);
	while (num / divider != 0)
	{
		divider *= charset_len;
		len++;
		if (num / divider == 0)
			return (len);
	}
	return (1);
}

static void		ft_write_num(char *string, size_t num, size_t len, char *c_set)
{
	int		multi;
	size_t	charset_len;

	charset_len = ft_strlen(c_set);
	multi = charset_len;
	if (num < 0)
		num *= -1;
	while (len > 0)
	{
		string[len - 1] = c_set[num % multi];
		num = num / charset_len;
		len--;
	}
}

char			*ft_itoa_base(size_t n, char *charset)
{
	char		*num_s;
	size_t		num_len;

	num_len = ft_num_size(n, ft_strlen(charset));
	num_s = ft_calloc(num_len + 1, sizeof(char));
	if (!num_s)
		return (0);
	ft_write_num(num_s, n, num_len, charset);
	return (num_s);
}
