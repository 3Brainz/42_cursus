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

int just_one_player(char **map)
{
	int y_index;
	int x_index;
	char pos = 0;
	char c;

	y_index = 0;
	x_index = 0;
	while (map[y_index])
	{
		x_index = 0;
		while ((c = map[y_index][x_index]))
		{
			if (is_in_cset(c, "NOWS"))
			{
				if(!pos)
					pos = c;
				else
					return (0);
			}
			x_index++;
		}
		y_index++;
	}
	if (!pos)
		return (0);
	return (1);
}
/*
void where_is_the_player(char **map, t_player *player)
{

}*/

int	is_map_valid(char **map)
{
	char **we = map;
	we = 0;
	return (1);
	return (0);
}
