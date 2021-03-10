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

/*static void print_keys(t_keys *keys)
{
	printf("w:%i\na:%i\ns:%i\nd:%i\nl:%i\nr:%i\n", keys->w_key, keys->a_key,keys->s_key,keys->d_key, keys->left_arrow, keys->right_arrow);
}*/

int update(t_window *window)
{
	t_data		image;

	new_image(&image, window, 1980, 1020);
	minimap_img(&image, window->game_v, 3, 60);
	mlx_put_image_to_window(window->mlx, window->mlx_win, image.img, 0, 0);
	mlx_destroy_image(window->mlx, image.img);
	//print_keys(window->keys);
	return (1);
}

int main(void)
{
	
	t_game_v	game_v[1];
	t_window	window;
	

	game_v_cleaner(game_v);
	if(!game_v_filler(game_v, "./map.cub"))
		return (0);
	window.game_v = game_v;
	clean_window_struct(&window);
	start_win(&window, game_v);
	
	mlx_hook(window.mlx_win, 06, 0L, mouse_pos_mov, &window);
	mlx_hook(window.mlx_win, 02, 0L, key_hook_in, &window);
	mlx_hook(window.mlx_win, 03, 0L, key_hook_out, &window);
	mlx_loop_hook(window.mlx, update, &window);
	mlx_loop(window.mlx);
}
