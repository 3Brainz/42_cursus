#include "../libcub.h"

void	ver_line(int x_cord, int y_start, int y_end, int color, t_data *img)
{
	/*
	y_start -= 300;
	y_end -= 300;
	if (y_end >= 1080)
		y_end = 1080;
		*/
	while(y_start <= y_end)
	{
		my_mlx_pixel_put(img, x_cord, y_start, color);
		y_start++;
	}
}

void	cast_ray(t_player *player, t_game_v *game_v, t_data *img)
{
	int x = 0;
	while (x < game_v->res_w_nu)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)game_v->res_w_nu - 1; //x-coordinate in camera space
		double rayDirX = player->plane->dir_x - player->plane->plane_x * cameraX;
		double rayDirY = player->plane->dir_y - player->plane->plane_y * cameraX;
		//which box of the map we're in
		int mapX = (int)(player->pos_x);
		int mapY = (int)(player->pos_y);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->pos_x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->pos_y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
			}
			else
			{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
			}
			//Check if ray has hit a wall
			if(game_v->map[mapY][mapX] == '1') hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - player->pos_x + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - player->pos_y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(game_v->res_h_nu / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game_v->res_h_nu / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + game_v->res_h_nu / 2;
		if(drawEnd >= game_v->res_h_nu || drawEnd < 0)drawEnd = game_v->res_h_nu - 1;

		//choose wall color
		int color;
		switch(game_v->map[mapY][mapX])
		{
			case 1:  color = 0x00FF0000;    break; //red
			case 2:  color = 0x00FF0000;  break; //green
			case 3:  color = 0x00FF0000;   break; //blue
			case 4:  color = 0x00FF0000;  break; //white
			default: color = 0x00FF0000; break; //yellow
		}

		//give x and y sides different brightness
		if(side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		ver_line(x, drawStart, drawEnd, color, img);
	//_________________________________________________________________
		x++;
	}
}
