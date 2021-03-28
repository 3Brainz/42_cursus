/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_engines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:15:56 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 18:15:58 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_flagger(t_flags *flags, char flag)
{
	if (flag == '-')
		flags->flag_minus = 1;
	if (flag == '0')
		flags->flag_zero = 1;
}

void	ft_width_handler(t_flags *flags, char c, va_list list)
{
	int width;

	if (flags->star_width)
		return ;
	if (c == '*')
	{
		width = va_arg(list, long int);
		if (width < 0)
		{
			flags->flag_minus = 1;
			width *= -1;
		}
		flags->width = width;
		flags->star_width = 1;
	}
	else if (ft_isdigit(c))
		flags->width = (flags->width * 10) + ft_ctoi(c);
}

void	ft_precision_handler(t_flags *flags, char c, va_list list)
{
	int precision;

	if (flags->star_dot)
		return ;
	if (c == '*')
	{
		precision = va_arg(list, long int);
		if (precision < 0)
		{
			flags->dot = 0;
			return ;
		}
		flags->precision = precision;
		flags->star_dot = 1;
	}
	else if (ft_isdigit(c))
		flags->precision = (flags->precision * 10) + ft_ctoi(c);
}

void	ft_type_parser(t_flags *flags, char c)
{
	if (ft_is_conversion(c))
		flags->type = c;
}

size_t	flag_filler(char *str, t_flags *flags, va_list list)
{
	size_t flag_index;

	flag_index = 0;
	while (ft_is_flag(str[flag_index]))
		ft_flagger(flags, str[flag_index++]);
	while (ft_is_width(str[flag_index]))
		ft_width_handler(flags, str[flag_index++], list);
	if (str[flag_index] == '.')
	{
		flags->dot = 1;
		flag_index++;
		while (ft_is_width(str[flag_index]))
			ft_precision_handler(flags, str[flag_index++], list);
	}
	ft_type_parser(flags, str[flag_index]);
	if (flags->type)
		flag_index++;
	if (flags->flag_minus && flags->flag_zero)
		flags->flag_zero = 0;
	return (flag_index);
}
