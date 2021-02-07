/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:16:30 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 18:16:31 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	type_manager(t_flags *flags, va_list list)
{
	if (flags->type == 'c')
		return (char_printer(flags, list));
	if (flags->type == 'i' || flags->type == 'd')
		return (dio_printer(flags, list));
	if (flags->type == 'u')
		return (unsigned_printer(flags, list));
	if (flags->type == 'x')
		return (unsigned_base_printer(flags, list, "0123456789abcdef"));
	if (flags->type == 'X')
		return (unsigned_base_printer(flags, list, "0123456789ABCDEF"));
	if (flags->type == 's')
		return (string_printer(flags, list));
	if (flags->type == '%')
		return (percentage_printer(flags));
	if (flags->type == 'p')
		return (pointer_base_printer(flags, list, "0123456789abcdef"));
	return (0);
}
