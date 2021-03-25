/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:12:48 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/03 16:12:51 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

int		first_last_row(char *row)
{
	int		index;
	char	c;

	index = 0;
	if (ft_strlen(row) == 0)
		return (0);
	while ((c = row[index]))
	{
		if (c != ' ' && c != '1')
			return (0);
		index++;
	}
	return (1);
}

int		zero_after_end(char *prev, char *curr, char *next)
{
	int target_len;
	int curr_len;

	curr_len = ft_strlen(curr);
	if (ft_strlen(prev) > ft_strlen(next))
		target_len = ft_strlen(next);
	else
		target_len = ft_strlen(prev);
	if (curr_len <= target_len && curr[curr_len - 1] == '1')
		return (1);
	else if (curr_len > target_len)
	{
		target_len--;
		while (curr[target_len])
		{
			if (curr[target_len] != '1')
				return (0);
			target_len++;
		}
		return (1);
	}
	return (0);
}

int		check_around_walkables(int index, char *prev, char *curr, char *next)
{
	if (prev[index] == ' ')
		return (0);
	if (next[index] == ' ')
		return (0);
	if (curr[index - 1] == ' ')
		return (0);
	if (curr[index + 1] == ' ')
		return (0);
	return (1);
}

int		check_zeroes(char *prev, char *curr, char *next)
{
	int min_len;
	int index;

	index = 0;
	if (ft_strlen(curr) < 3)
		return (0);
	min_len = (int)fmin(ft_strlen(prev), ft_strlen(curr));
	min_len = (int)fmin(min_len, ft_strlen(next));
	if (curr[index] == '0')
		return (0);
	index++;
	while (curr[index + 1] && index < min_len - 1)
	{
		if (curr[index] == '0' || curr[index] == '2')
		{
			if (curr[index] == '0' || curr[index] == '2')
			{
				if (!check_around_walkables(index, prev, curr, next))
					return (0);
			}
		}
		index++;
	}
	return (1);
}

int		intermidiate_row(char *prev, char *curr, char *next)
{
	if (!zero_after_end(prev, curr, next))
		return (0);
	if (!check_zeroes(prev, curr, next))
		return (0);
	return (1);
}
