/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 19:01:25 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/07 19:01:26 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	prt_m(char **string, size_t *added, t_flags *flags, va_list list_v)
{
	size_t	flag_size;

	flag_size = 0;
	if (**string == '%')
	{
		*string += 1;
		flag_size = flag_filler((char *)*string, flags, list_v);
		if (flags->type)
			*added += type_manager(flags, list_v);
		*string += flag_size - 1;
		flag_cleaner(flags);
	}
	else
	{
		write(1, *string, 1);
		*added += 1;
	}
	flag_size = 0;
}

int			ft_printf(const char *string, ...)
{
	t_flags	flags;
	va_list	list_v;
	size_t	added;

	added = 0;
	flag_cleaner(&flags);
	va_start(list_v, string);
	while (*string)
	{
		prt_m((char **)&string, &added, &flags, list_v);
		string++;
	}
	va_end(list_v);
	return (added);
}
