/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:11:37 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/02 10:11:39 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

int ft_numlen(char **str)
{
	int index;

	index = 0;
	while(ft_isdigit(**str))
	{
		*str += 1;
		index++;
	}
	return (index);
}

void ft_jump_spaces(char **str)
{
	while (**str == ' ' && **str)
		*str += 1;
}

