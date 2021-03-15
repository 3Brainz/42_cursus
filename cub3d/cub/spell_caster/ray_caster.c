#include "../libcub.h"

void	ver_line(int x_cord, int y_start, int y_end, int color, t_data *img)
{
	while(y_start < y_end)
	{
		my_mlx_pixel_put(img, x_cord, y_start, color);
		y_start++;
	}
}

void	cast_ray(t_player *player, t_game_v *game_v, t_data *img)
{
	int x;

	x = 0;
	while (x < game_v->res_w_nu)
	{
		double ray_dir_x;
		double ray_dir_y;
		double camera_x;

		camera_x = 2 * x / (double)game_v->res_w_nu - 1;
		ray_dir_x = player->plane->dir_x + player->plane->plane_x * camera_x;
		ray_dir_y = player->plane->dir_y + player->plane->plane_y * camera_x;

		double delta_dist_x;
		double delta_dist_y;

		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);

		double perp_wall_dist;

		int map_x = (int)(player->pos_x);
      	int map_y = (int)(player->pos_y);

		double side_dist_x;
		double side_dist_y;
		int step_x;
		int step_y;
		int hit = 0;
		int side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player->pos_y) * delta_dist_y;
		}
		 while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
			}
			else
			{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
			}
			if (game_v->map[map_x][map_y] > 0)
				hit = 1;
		} 	
		if (side == 0)
			perp_wall_dist = (map_x - player->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - player->pos_y + (1 - step_y) / 2) / ray_dir_y;

		int line_height;
		line_height = (int)(game_v->res_h_nu / perp_wall_dist);
		int draw_start;
		draw_start = -line_height / 2 + game_v->res_h_nu / 2;
		if(draw_start < 0)
			draw_start = 0;
     	int draw_end;
		 draw_end = line_height / 2 + game_v->res_h_nu / 2;
      	if(draw_end >= game_v->res_h_nu)
		  	draw_end = game_v->res_h_nu - 1;

		int color;
		
		switch(game_v->map[map_x][map_y])
     	{
        case 1:  color =  0x00FF0000;  break; //red
        case 2:  color =  0x00FF0000;  break; //green
        case 3:  color =  0x00FF0000;   break; //blue
        case 4:  color =  0x00FF0000;  break; //white
        default: color =  0x00FF0000; break; //yellow
     	}
		if (side == 1)
			color = color / 2;
		ver_line(x, draw_start, draw_end, color, img);
		x++;
	}		
}