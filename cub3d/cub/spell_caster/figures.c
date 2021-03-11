#include "../libcub.h"

void print_pg(t_data *img, t_window *window, int dim)
{
	int x;
	int y;

	x = window->player->pos_x - dim / 2;
	y = window->player->pos_y - dim / 2;
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
	y =	origins[2] - size / 2;
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