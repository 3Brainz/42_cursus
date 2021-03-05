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

int main()
{
	
	t_game_v	game_v;
	t_window	window;
	t_data		image;

	game_v_cleaner(&game_v);
	game_v_filler(&game_v, "./map.cub");
	start_win(&window, &game_v);
	new_image(&image, &window, 1920, 1080);
	my_mlx_pixel_put(&image, 0, 0, 0x00FF0000);
	mlx_put_image_to_window(window.mlx, window.mlx_win, image.img, 0, 0);
	mlx_loop(window.mlx);
	return (0);
}
