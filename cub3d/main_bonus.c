#include "cub/libcub.h"
#include "cub/libcub_bonus.h"

int update(t_window *window)
{
	t_data		image;

	player_movement(window->keys, window->player, window->game_v->map);
	mouse_rot(window);
	new_image(&image, window,
				window->game_v->res_w_nu, window->game_v->res_h_nu);
	cast_ray(window->player, window->game_v, &image, window);
	minimap_img(&image, window, window->player, 5);
	mlx_put_image_to_window(window->mlx, window->mlx_win, image.img, 0, 0);
	mlx_destroy_image(window->mlx, image.img);
	if(window->keys->esc)
		close_game(window);
	return (1);
}

void	engine_starter(t_window *window)
{
	mlx_hook(window->mlx_win, 06, 0L, mouse_pos_mov, window);
	mlx_hook(window->mlx_win, 02, 0L, key_hook_in, window);
	mlx_hook(window->mlx_win, 03, 0L, key_hook_out, window);
	mlx_loop_hook(window->mlx, update, window);
	mlx_loop(window->mlx);
}

int main(int argc, char **argv)
{
	t_game_v	game_v[1];
	t_window	window;
	int			w_n;

	w_n = 0;
	if (argc > 1 && argc < 3)
	{
		if (check_suffix(argv[1], ".cub"))
		{
			game_v_cleaner(game_v);
			if(!game_v_filler(game_v, argv[1]))
				return (0);
			game_v->bonus = 1;
			window.game_v = game_v;
			clean_window_struct(&window);
			start_win(&window, game_v);
			if (!validator(game_v))
				return (0);
			textures_filler(&window);
			engine_starter(&window);
		}
		else
			w_n = 1;
	}
	else
		w_n = 1;
	if (w_n)
		printf ("Error\nwrong number of arguments, or wrong arguments");
}
