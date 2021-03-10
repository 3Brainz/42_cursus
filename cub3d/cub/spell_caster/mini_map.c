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

void	minimap_img(t_data *img, t_game_v *game_v, int fac, int d_f_b)
{
	int print_x;
	int print_y;
	int s_size[2];

	s_size[0] = game_v->res_w_nu;
	s_size[1] = game_v->res_h_nu;
	print_x = d_f_b;
	print_y = s_size[1] - s_size[1] / 4;
	while (print_y < s_size[1] - d_f_b)
	{
		print_x = d_f_b;
		while (print_x < s_size[0] / fac)
		{
			my_mlx_pixel_put(img, print_x, print_y, 0x00FF0000);
			print_x++;
		}
		print_y++;
	}
}
