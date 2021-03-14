#include "../libcub.h"

void	cast_ray(t_player *player, t_game_v *game_v)
{
	int x;
	double ray_dir_x;
	double ray_dir_y;
	double camera_x;

	x = 0;
	while (x < game_v->res_w_nu)
	{
		camera_x = 2 * x / (double)game_v->res_w_nu - 1;
		ray_dir_x = player->plane->dir_x + player->plane->plane_x * camera_x;
		ray_dir_y = player->plane->dir_y + player->plane->plane_y * camera_x;
		x++;
	}		
}