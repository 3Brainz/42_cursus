/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:17:25 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 18:17:27 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*zero_filled_string(size_t len, int with_minus)
{
	char	*str;
	size_t	index;

	index = 0;
	str = (char *)ft_calloc(sizeof(char), len + 1 + with_minus);
	while (index < len + with_minus)
		str[index++] = '0';
	if (with_minus)
		str[0] = '-';
	return (str);
}

char	*appendix_creator(char fill, size_t len, int with_minus)
{
	char	*appendix;
	size_t	index;

	index = 0;
	appendix = (char *)ft_calloc(sizeof(char), len + 1);
	while (index < len)
	{
		appendix[index] = fill;
		index++;
	}
	if (with_minus)
		appendix[0] = '-';
	return (appendix);
}

char	*appendixer(char **str, size_t g_len, t_flags *flags)
{
	char *appendix;
	char *temp;

	if (flags->flag_minus)
	{
		appendix = appendix_creator(' ', g_len, 0);
		temp = ft_strjoin(*str, appendix);
	}
	else if (flags->flag_zero && !flags->dot)
	{
		if (flags->num_m)
			appendix = appendix_creator('0', g_len + 1, 1);
		else
			appendix = appendix_creator('0', g_len, 0);
		temp = ft_strjoin(appendix, *str + flags->num_m);
	}
	else
	{
		appendix = appendix_creator(' ', g_len, 0);
		temp = ft_strjoin(appendix, *str);
	}
	free(appendix);
	return (temp);
}

char	*appendixer_char(t_flags *flags, size_t *r_val, char c)
{
	char	*res;
	char	*appendix;

	appendix = appendix_creator(' ', flags->width, 0);
	if (flags->flag_minus)
		appendix[0] = c;
	else
		appendix[flags->width - 1] = c;
	res = appendix;
	*r_val = flags->width;
	return (res);
}

void	append_s(char **res, char **temp, t_flags *flags, size_t len)
{
	char	*appendix;

	appendix = appendix_creator(' ', flags->width - len, 0);
	if (flags->flag_minus)
		*temp = ft_strjoin(*res, appendix);
	else
	{
		if (flags->flag_zero)
		{
			free(appendix);
			appendix = appendix_creator('0', flags->width - len, 0);
		}
		*temp = ft_strjoin(appendix, *res);
	}
	free(*res);
	free(appendix);
	*res = *temp;
}
