#include "../libcub.h"

void	add_minimap_to_img(t_data *image, t_game_v *game_v, int factor)
{
	int print_x;
	int print_y;

	factor = 1;
	print_x = 0;
	print_y = 0;
	while (print_y < game_v->res_h_nu)
	{
		print_x = 0;
		while(print_x < game_v->res_w_nu)
		{
			my_mlx_pixel_put(image, print_x, print_y, 0x00FF0000);
			print_x++;
		}
		print_y++;
	}
}