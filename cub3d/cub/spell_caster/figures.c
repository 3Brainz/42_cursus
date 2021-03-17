#include "../libcub.h"

void print_pg(t_data *img, t_window *window, int dim)
{
	int x;
	int y;

	x = (window->player->pos_x - dim / 2) * dim;
	y = (window->player->pos_y - dim / 2) * dim;
	while (y < window->player->pos_y + dim / 2)
	{
		x = window->player->pos_x - dim / 2;
		while (x < window->player->pos_x + dim / 2)
		{
			if (x > 0 && x < window->game_v->res_w_nu &&
				y > 0 && y < window->game_v->res_h_nu)
				my_mlx_pixel_put(img, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void print_rect(t_data *img, float *origins, t_window *window, float size)
{
	int x;
	int y;

	x = origins[1] - size / 2;
	y =	origins[0] - size / 2;
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

void	print_sky_and_floor(t_data *img, t_game_v *game_v)
{
	int y_index;
	int x_index;

	y_index = 0;
	x_index = 0;
	while (y_index < game_v->res_h_nu / 2)
	{
		x_index = 0;
		while (x_index < game_v->res_w_nu)
		{
			my_mlx_pixel_put(img, x_index, y_index, game_v->ceiling_color->n_color);
			x_index++;
		}
		y_index++;
	}
	while (y_index < game_v->res_h_nu)
	{
		x_index = 0;
		while (x_index < game_v->res_w_nu)
		{
			my_mlx_pixel_put(img, x_index, y_index, game_v->floor_color->n_color);
			x_index++;
		}
		y_index++;
	}
}