/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_machines_nu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:17:15 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 18:17:16 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	dio_printer(t_flags *flags, va_list list)
{
	int		i;
	char	*str;
	char	*res;
	size_t	r_val;

	i = va_arg(list, int);
	if (i < 0)
		flags->num_m = 1;
	if (!(flags->dot && i == 0))
		str = ft_itoa(i);
	else
		str = ft_strdup("");
	res = ft_integer_positioner(&str, flags, NULL);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}

size_t	unsigned_printer(t_flags *flags, va_list list)
{
	unsigned	i;
	char		*str;
	char		*res;
	size_t		r_val;

	i = va_arg(list, unsigned);
	if (!(flags->dot && i == 0))
		str = ft_uitoa(i);
	else
		str = ft_strdup("");
	res = ft_integer_positioner(&str, flags, NULL);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}

size_t	unsigned_base_printer(t_flags *flags, va_list list, char *base)
{
	unsigned	i;
	char		*str;
	char		*res;
	size_t		r_val;

	i = va_arg(list, unsigned);
	if (!(flags->dot && i == 0))
		str = ft_itoa_base(i, base);
	else
		str = ft_strdup("");
	res = ft_integer_positioner(&str, flags, NULL);
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}

size_t	pointer_base_printer(t_flags *flags, va_list list, char *base)
{
	size_t		i;
	char		*str;
	char		*res;
	size_t		r_val;

	i = va_arg(list, size_t);
	if (!(flags->dot && i == 0))
		str = ft_itoa_base(i, base);
	else
		str = ft_strdup("");
	res = ft_integer_positioner(&str, flags, "0x");
	ft_putstr_fd(res, 1);
	r_val = ft_strlen(res);
	free(res);
	free(str);
	return (r_val);
}
