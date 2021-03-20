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

void print_keys(t_keys *keys)
{
	printf("w:%i\na:%i\ns:%i\nd:%i\nl:%i\nr:%i\nsh:%i\ne:%i\n", keys->w_key, keys->a_key,keys->s_key,keys->d_key, keys->left_arrow, keys->right_arrow, keys->shift, keys->esc);
}

 void print_player(t_player *player)
{
	printf("pos_x:%f,pos_y:%f,inclination:%f\n",player->pos_x, player->pos_y, player->inclination);
}

int update(t_window *window)
{
	t_data		image;

	player_movement(window->keys, window->player, window->game_v->map);
	//print_player(window->player);
	//print_keys(window->keys);
	new_image(&image, window,
				window->game_v->res_w_nu, window->game_v->res_h_nu);
	//print_sky_and_floor(&image, window->game_v);
	cast_ray(window->player, window->game_v, &image, window);
	minimap_img(&image, window, window->player);
	//print_pg(&image, window, 10);
	mlx_put_image_to_window(window->mlx, window->mlx_win, image.img, 0, 0);
	mlx_destroy_image(window->mlx, image.img);
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
	/*
	for(int x = 0; x < texWidth; x++)
	for(int y = 0; y < texHeight; y++)
	{
	int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
		//int xcolor = x * 256 / texWidth;
	int ycolor = y * 256 / texHeight;
    int xycolor = y * 128 / texHeight + x * 128 / texWidth;
	texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
	texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
    texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
    texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
    texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
    texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
    texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
    texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
    texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	}*/
	if (!validator(game_v, &window))
	{
		return (0);
	}
	// texture[0].img = mlx_xpm_file_to_image(window.mlx, "cub/brick.xpm", &texture[0].img_width, &texture[0].img_height);
	// texture[0].addr = (int *)mlx_get_data_addr(texture[0].img, &texture[0].bits_per_pixel, &texture[0].line_length, &texture[0].endian);
	// texture[1].img = mlx_xpm_file_to_image(window.mlx,"cub/grass.xpm", &texture[1].img_width, &texture[1].img_height);
	// texture[1].addr = (int *)mlx_get_data_addr(texture[1].img, &texture[1].bits_per_pixel, &texture[1].line_length, &texture[1].endian);
	// texture[2].img = mlx_xpm_file_to_image(window.mlx, "cub/metal.xpm", &texture[2].img_width, &texture[2].img_height);
	// texture[2].addr = (int *)mlx_get_data_addr(texture[2].img, &texture[2].bits_per_pixel, &texture[2].line_length, &texture[2].endian);
	// texture[3].img = mlx_xpm_file_to_image(window.mlx, "cub/stone.xpm", &texture[3].img_width, &texture[3].img_height);
	// texture[3].addr = (int *)mlx_get_data_addr(texture[3].img, &texture[3].bits_per_pixel, &texture[3].line_length, &texture[3].endian);

	mlx_hook(window.mlx_win, 06, 0L, mouse_pos_mov, &window);
	mlx_hook(window.mlx_win, 02, 0L, key_hook_in, &window);
	mlx_hook(window.mlx_win, 03, 0L, key_hook_out, &window);
	mlx_loop_hook(window.mlx, update, &window);
	mlx_loop(window.mlx);
}
