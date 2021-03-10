/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:20:58 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/03 15:20:59 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void	initialize_vars(int vars_number, ...)
{
	va_list		list;
	void		*variable;

	va_start(list, vars_number);
	while (vars_number > 0)
	{
		variable = va_arg(list, void *);
		*(long long *)variable = 0;
		vars_number--;
	}
	va_end(list);
}

void	free_if_exists(void **var)
{
	if (*var)
		free(*var);
	*var = 0;
}

void	free_mat(void **mat)
{
	size_t index;

	index = 0;
	if(mat)
	{
		while(mat[index])
		{
			free_if_exists(&mat[index]);
			index++;
		}
	}
}