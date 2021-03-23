/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:12:48 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/03 16:12:51 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

int	just_right_chars(char **map)
{
	int x;
	int y;
	
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_in_cset(map[y][x], "012 NSWE"))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	is_map_valid(char **map)
{
	char **we = map;

	we = 0;
	if (just_one_player(map) && just_right_chars(map))
	{
		return (1);
	}
	return (0);
}
