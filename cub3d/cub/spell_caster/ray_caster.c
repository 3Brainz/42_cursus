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

typedef struct	s_caster
{
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY; 
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
}				t_caster;

void	zero_caster(t_caster *caster)
{
	caster->cameraX = 0;
	caster->rayDirX = 0;
	caster->rayDirY = 0;
	caster->mapX = 0;
	caster->mapY = 0;
	caster->sideDistX = 0;
	caster->sideDistY = 0;
	caster->deltaDistX = 0;
	caster->deltaDistY = 0;
	caster->perpWallDist = 0;
	caster->stepX = 0;
	caster->stepY = 0;
	caster->hit = 0;
	caster->side = 0;
	caster->lineHeight = 0;
	caster->drawStart = 0;
	caster->drawEnd = 0;
}

void	ray_pos_and_dir(t_caster *caster, t_game_v *game_v,t_player *player, int x)
{
	caster->cameraX = 2 * x / (double)game_v->res_w_nu - 1;
	caster->rayDirX = player->plane->dir_x - player->plane->plane_x * caster->cameraX;
	caster->rayDirY = player->plane->dir_y - player->plane->plane_y * caster->cameraX;
	caster->mapX = (int)(player->pos_x);
	caster->mapY = (int)(player->pos_y);
	caster->deltaDistX = fabs(1 / caster->rayDirX);
	caster->deltaDistY = fabs(1 / caster->rayDirY);
}

void	ray_collider(t_caster *caster, t_player *player)
{
	caster->hit = 0;
	if(caster->rayDirX < 0)
	{
		caster->stepX = -1;
		caster->sideDistX = (player->pos_x - caster->mapX) * caster->deltaDistX;
	}
	else
	{
		caster->stepX = 1;
		caster->sideDistX = (caster->mapX + 1.0 - player->pos_x) * caster->deltaDistX;
	}
	if(caster->rayDirY < 0)
	{
		caster->stepY = -1;
		caster->sideDistY = (player->pos_y - caster->mapY) * caster->deltaDistY;
	}
	else
	{
		caster->stepY = 1;
		caster->sideDistY = (caster->mapY + 1.0 - player->pos_y) * caster->deltaDistY;
	}
}

void	ray_dda(t_caster *caster, t_game_v *game_v)
{
	while (caster->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(caster->sideDistX < caster->sideDistY)
			{
				caster->sideDistX += caster->deltaDistX;
				caster->mapX += caster->stepX;
				caster->side = 0;
			}
			else
			{
				caster->sideDistY += caster->deltaDistY;
				caster->mapY += caster->stepY;
				caster->side = 1;
			}
			//Check if ray has hit a wall
			if(game_v->map[caster->mapY][caster->mapX] == '1') 
				caster->hit = 1;
		}
}

void	line_measure_dist(t_caster *caster, t_game_v *game_v, t_player *player)
{
	if(caster->side == 0)
		caster->perpWallDist = (caster->mapX - player->pos_x + (1 - caster->stepX) / 2) / caster->rayDirX;
	else	
		caster->perpWallDist = (caster->mapY - player->pos_y + (1 - caster->stepY) / 2) / caster->rayDirY;
	caster->lineHeight = (int)(game_v->res_h_nu / caster->perpWallDist);
	caster->drawStart = -caster->lineHeight / 2 + game_v->res_h_nu / 2;
	if(caster->drawStart < 0)
		caster->drawStart = 0;
	caster->drawEnd = caster->lineHeight / 2 + game_v->res_h_nu / 2;
	if(caster->drawEnd >= game_v->res_h_nu || caster->drawEnd < 0)
		caster->drawEnd = game_v->res_h_nu - 1;
}

void	cast_ray(t_player *player, t_game_v *game_v, t_data *img)
{
	t_caster caster[1];
	int x;

	x = 0;
	zero_caster(caster);
	while (x < game_v->res_w_nu)
	{
		zero_caster(caster);
		ray_pos_and_dir(caster, game_v, player, x);
		ray_collider(caster, player);
		ray_dda(caster, game_v);
		line_measure_dist(caster, game_v, player);
		int color = 0x00FF0000;
		ver_line(x, caster->drawStart, caster->drawEnd, color, img);
		x++;
	}
}








/*
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
		int color = 0x00FF0000;
		//give x and y sides different brightness
		//if(side == 1) {color = color / 2;}
		//draw the pixels of the stripe as a vertical line
		ver_line(x, drawStart, drawEnd, color, img);
		x++;
	}
}
*/