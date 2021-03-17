/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:35:11 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/10 10:35:13 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void	minimap_img(t_data *img, t_window *window, int ratio, t_player *player)
{
	size_t mat_index = 0;
	size_t index = 0;
	size_t x = 0;
	size_t y = 0;
	while (window->game_v->map[mat_index])
	{
		index = 0;
		while (index < ft_strlen(window->game_v->map[mat_index]))
		{
			x = index * ratio;
			while(x < ratio * (index + 1))
			{
				y = ratio * mat_index;
				while (y < ratio * (mat_index + 1))
				{
					if (window->game_v->map[mat_index][index] == '1')
						my_mlx_pixel_put(img, x, y, 0x00FF0000);
					y++;
				}
				x++;
			}
			index++;
		}
		mat_index++;
	}
	float origins[2];
	origins[1] = player->pos_x * ratio;
	origins[0] = player->pos_y * ratio;
	print_rect(img, origins, window, 50);
}
/*
void	minimap_img(t_data *img, t_game_v *game_v)
{
	float dimensions[2];
	int factor;
	int variable;

	factor = 0;
	dimensions[1] = game_v->map_size->size_x;
	dimensions[0] = game_v->map_size->size_y;
	if (dimensions[0] > dimensions[1])
	{
		variable = dimensions[0];
		while (va)
	}
	else
	{
		variable = dimensions[1];
	}
}*/