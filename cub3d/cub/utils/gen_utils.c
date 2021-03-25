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
	if (mat)
	{
		while (mat[index])
		{
			free_if_exists(&mat[index]);
			index++;
		}
	}
}

int		check_suffix(char *str, char *suffix)
{
	int suff_len;
	int index;

	suff_len = ft_strlen(suffix);
	index = ft_strlen(str);
	if (index > suff_len)
	{
		while (suff_len)
		{
			if (suffix[suff_len - 1] != str[index - 1])
				return (0);
			suff_len--;
			index--;
		}
		return (1);
	}
	return (0);
}
