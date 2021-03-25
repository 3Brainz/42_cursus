#include "cub/libcub.h"
#include "cub/libcub_bonus.h"

int update(t_window *window)
{
	t_data		image;

	player_movement(window->keys, window->player, window->game_v->map);
	new_image(&image, window,
				window->game_v->res_w_nu, window->game_v->res_h_nu);
	cast_ray(window->player, window->game_v, &image, window);
	minimap_img(&image, window, window->player, 5);
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
	if (!validator(game_v))
		return (0);
	textures_filler(&window);
	mlx_hook(window.mlx_win, 06, 0L, mouse_pos_mov, &window);
	mlx_hook(window.mlx_win, 02, 0L, key_hook_in, &window);
	mlx_hook(window.mlx_win, 03, 0L, key_hook_out, &window);
	mlx_loop_hook(window.mlx, update, &window);
	mlx_loop(window.mlx);
}
