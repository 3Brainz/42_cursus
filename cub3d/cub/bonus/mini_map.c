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

int		calc_ratio(t_game_v *game_v, int relative_size)
{
	int mat_len_x;
	int mat_len_y;
	int ratio;

	mat_len_x = game_v->map_size->size_x;
	mat_len_y = game_v->map_size->size_y;
	if (mat_len_x > mat_len_y)
		ratio = (game_v->res_w_nu / relative_size) / mat_len_x;
	else
		ratio = (game_v->res_h_nu / relative_size) / mat_len_y;
	return (ratio);
}

void	print_rect(t_data *img, float *origins, t_window *window, float size)
{
	int x;
	int y;

	x = origins[1] - size / 2;
	y = origins[0] - size / 2;
	while (y < origins[0] + size / 2)
	{
		x = origins[1] - size / 2;
		while (x < origins[1] + size / 2)
		{
			if (x > 0 && x < window->game_v->res_w_nu &&
				y > 0 && y < window->game_v->res_h_nu)
				my_mlx_pixel_put(img, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void	minimap_img(t_data *img, t_window *window,t_player *player, int min_fract)
{
	size_t	mat_index = -1;
	float	origins[2];
	size_t	index = -1;
	size_t	x = -1;
	size_t	y = -1;

	int ratio = calc_ratio(window->game_v, min_fract);
	while (window->game_v->map[++mat_index])
	{
		index = -1;
		while (++index < ft_strlen(window->game_v->map[mat_index]))
		{
			x = index * ratio - 1;
			while(++x < ratio * (index + 1))
			{
				y = ratio * mat_index - 1;
				while (++y < ratio * (mat_index + 1))
				{
					if (window->game_v->map[mat_index][index] == '1')
						my_mlx_pixel_put(img, x, y, 0x000000FF);
					else if (window->game_v->map[mat_index][index] == '2')
						my_mlx_pixel_put(img, x, y, 0x0000FF00);
					else
						my_mlx_pixel_put(img, x, y, 0x00FF0000);
				}
			}
		}
	}
	origins[1] = player->pos_x * ratio;
	origins[0] = player->pos_y * ratio;
	print_rect(img, origins, window, ratio);
}
