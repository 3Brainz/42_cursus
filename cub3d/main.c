/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:32:07 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/27 11:32:09 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub/libcub.h"
#include <mlx.h>

int game(t_window *window)
{
	int x_pos;
	int y_pos;
	window->mouse_pos->pos_x += 1;
	window->mouse_pos->pos_y = 0;
	x_pos = window->mouse_pos->pos_x;
	y_pos = window->mouse_pos->pos_y;
	//mlx_mouse_get_pos(window->mlx_win, &x_pos, &y_pos);
	printf("x_pos:%i\n",x_pos);
	return (0);
}

int main()
{
	
	t_game_v	game_v;
	t_window	window;
	t_data		image;

	game_v_cleaner(&game_v);
	game_v_filler(&game_v, "./map.cub");
	clean_window_struct(&window);
	start_win(&window, &game_v);
	new_image(&image, &window, game_v.res_w_nu, game_v.res_h_nu);
	my_mlx_pixel_put(&image, 0, 0, 0x00FF0000);
	int x = 0;
	int y = 0;
	while (x < 100)
	{
		y = 0;
		while (y < 100)
		{
			my_mlx_pixel_put(&image, x+10, y+10, 0x00FF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(window.mlx, window.mlx_win, image.img, 0, 0);
	mlx_key_hook(window.mlx_win, key_hook, &window);
	mlx_mouse_hook(window.mlx_win, mouse_click, &window);
	//mlx_mouse_get_pos(window.mlx_win, &window.mouse_pos.pos_x, &window.mouse_pos.pos_y);
	mlx_loop_hook(window.mlx_win, &game, &window);
	mlx_loop(window.mlx);
	return (0);
}
