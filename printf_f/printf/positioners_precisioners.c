/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positioners_precisioners.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:17:41 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 18:17:42 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	integer_precisioner(char **str, t_flags *flags)
{
	char	*temp;
	char	*zeros;
	int		is_negative;

	is_negative = flags->num_m;
	if (ft_strlen(*str + is_negative) >= flags->precision)
		return ;
	else
	{
		zeros = zero_filled_string((flags->precision) - ft_strlen(*str) +
									is_negative, is_negative);
		temp = ft_strjoin(zeros, *str + is_negative);
		free(zeros);
		free(*str);
		*str = temp;
	}
}

char	*ft_integer_positioner(char **str, t_flags *flags, char *pre)
{
	size_t	len;
	size_t	g_index;
	size_t	g_len;
	char	*temp;

	g_len = 0;
	g_index = 0;
	integer_precisioner(str, flags);
	if (pre)
	{
		temp = ft_strjoin(pre, *str);
		free(*str);
		*str = temp;
	}
	len = ft_strlen(*str);
	if (flags->width > len)
	{
		g_len = flags->width - len;
		temp = appendixer(str, g_len, flags);
	}
	else
		temp = ft_strdup(*str);
	return (temp);
}

char	*ft_string_positioner(t_flags *flags, char *str)
{
	char	*res;
	char	*temp;
	size_t	len;

	if (flags->dot)
		res = ft_substr(str, 0, flags->precision);
	else
		res = ft_strdup(str);
	len = ft_strlen(res);
	if (flags->width > len)
		append_s(&res, &temp, flags, len);
	return (res);
}
