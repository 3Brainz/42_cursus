/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:16:04 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 18:16:06 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	flag_cleaner(t_flags *flags)
{
	flags->flag_minus = 0;
	flags->flag_zero = 0;
	flags->star_width = 0;
	flags->width = 0;
	flags->star_dot = 0;
	flags->dot = 0;
	flags->precision = 0;
	flags->num_m = 0;
	flags->type = 0;
}

int		is_in_charset(char c, char *charset)
{
	size_t charset_i;

	charset_i = 0;
	while (charset[charset_i])
	{
		if (c == charset[charset_i])
			return (1);
		charset_i++;
	}
	return (0);
}

int		ft_is_conversion(char c)
{
	if (is_in_charset(c, CONVERSION_VALUES))
		return (1);
	return (0);
}

int		ft_is_flag(char c)
{
	if (is_in_charset(c, FLAGS))
		return (1);
	return (0);
}

int		ft_is_width(char c)
{
	if (c == '*' || ft_isdigit(c))
		return (1);
	return (0);
}
