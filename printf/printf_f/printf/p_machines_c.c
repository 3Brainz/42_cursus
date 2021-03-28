/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_machines_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:16:44 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 18:16:46 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	char_printer(t_flags *flags, va_list list)
{
	char	c;
	char	*str;
	char	*res;
	char	*appendix;
	size_t	r_val;

	appendix = NULL;
	c = va_arg(list, int);
	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	if (flags->width > 1)
		res = appendixer_char(flags, &r_val, c);
	else
	{
		res = ft_strdup(str);
		r_val = ft_strlen(res);
	}
	if (r_val == 0)
		r_val = 1;
	ft_print_also_null(res, r_val);
	free(res);
	free(str);
	return (r_val);
}

size_t	string_printer(t_flags *flags, va_list list)
{
	char	*str;
	char	*res;
	int		allocated;
	size_t	r_val;

	allocated = 0;
	if (!(str = va_arg(list, char*)))
	{
		str = ft_strdup("(null)");
		allocated = 1;
	}
	res = ft_string_positioner(flags, str);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	if (allocated)
		free(str);
	return (r_val);
}

size_t	percentage_printer(t_flags *flags)
{
	char	*str;
	char	*res;
	size_t	r_val;

	str = ft_strdup("%");
	res = ft_integer_positioner(&str, flags, NULL);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}
