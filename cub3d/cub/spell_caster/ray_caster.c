#include "../libcub.h"

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
	caster->wallX = 0;
	caster->texX = 0;
	caster->step = 0;
	caster->texPos = 0;
	caster->texY = 0;
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

t_texture *texture_selector(t_window *window, t_caster *caster)
{
	if (caster->side == 0)
		{
			if (caster->rayDirX > 0)
				return (window->textuures->e_texture);
			else
				return (window->textuures->w_texture);
		}
		else
		{
			if (caster->rayDirY > 0)
				return(window->textuures->s_textture);
			else
				return(window->textuures->n_texture);
		}
}

void texturer(t_caster *caster, t_player *player, t_game_v *game_v, t_window *window)
{
	t_texture *texture;
	
	texture = texture_selector(window, caster);
	if(caster->side == 0)	
		caster->wallX = player->pos_y + caster->perpWallDist * caster->rayDirY;
	else
		caster->wallX = player->pos_x + caster->perpWallDist * caster->rayDirX;
	caster->wallX -= floor((caster->wallX));
	//x coordinate on the texture
	caster->texX = (int)(caster->wallX * (double)(texture->img_width));
	if(caster->side == 0 && caster->rayDirX > 0)
		caster->texX = texture->img_width - caster->texX - 1;
	if(caster->side == 1 && caster->rayDirY < 0)
		caster->texX = texture->img_width - caster->texX - 1;
	caster->step = 1.0 * texture->img_height / caster->lineHeight;
	caster->texPos = (caster->drawStart - game_v->res_h_nu / 2 + caster->lineHeight / 2) * caster->step;
}

void	ver_line(int x, t_caster *caster, t_window *window, t_data *img)
{
	int index;
	t_texture *texture;
	t_texture *skybox;
	index = 0;
	while (++index < caster->drawStart)
		if(!window->game_v->skybox)
			my_mlx_pixel_put(img, x, index, window->game_v->ceiling_color->n_color);
		else
		{
			skybox = window->textuures->skybox;
			my_mlx_pixel_put(img, x, index, skybox->addr[(int)(window->player->inclination * skybox->img_width) + index * skybox->img_width + x]);
		}
	while(++index < caster->drawEnd)
	{
		caster->texY = (int)caster->texPos & (texture->img_height - 1);
		caster->texPos += caster->step;
		texture = texture_selector(window, caster);
		my_mlx_pixel_put(img, x, index, texture->addr[texture->img_height * caster->texY + caster->texX]);
	}
	while(++index < window->game_v->res_h_nu)
		my_mlx_pixel_put(img, x, index, window->game_v->floor_color->n_color);
}

void	cast_ray(t_player *player, t_game_v *game_v, t_data *img, t_window *window)
{
	t_caster *caster;
	int x;

	x = 0;
	caster = player->caster;
	zero_caster(caster);
	while (x < game_v->res_w_nu)
	{
		zero_caster(caster);
		ray_pos_and_dir(caster, game_v, player, x);
		ray_collider(caster, player);
		ray_dda(caster, game_v);
		line_measure_dist(caster, game_v, player);
		texturer(caster, player, game_v, window);
		ver_line(x, caster, window, img);
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
			if(game_v->map[mapY][mapX] > '0') hit = 1;
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

//--------------------------------------------------------------------------------------//----------//------
		double wallX; //where exactly the wall was hit
			if(side == 0)	
			wallX = player->pos_y + perpWallDist * rayDirY;
		else
			wallX = player->pos_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;
		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - game_v->res_h_nu / 2 + lineHeight / 2) * step;

		//choose wall color
		// int color = 0x00FF0000;
		//give x and y sides different brightness
		//if(side == 1) {color = color / 2;}
		//draw the pixels of the stripe as a vertical line
		//ver_line(x, drawStart, drawEnd, game_v, img);
		int index;

		index = 0;

		while (index <= drawStart)
			{
				my_mlx_pixel_put(img, x, index, game_v->ceiling_color->n_color);
				index++;
			}
			while(index <= drawEnd)
			{
				int texY = (int)texPos & (texHeight - 1);
        		texPos += step;
				if (side == 0)
				{
					if (rayDirX > 0)
						my_mlx_pixel_put(img, x, index, texture[0][texHeight * texY + texX]);
					else
						my_mlx_pixel_put(img, x, index, texture[1][texHeight * texY + texX]);
				}
				else
				{
					if (rayDirY > 0)
						my_mlx_pixel_put(img, x, index, texture[2][texHeight * texY + texX]);
					else
						my_mlx_pixel_put(img, x, index, texture[3][texHeight * texY + texX]);
				}
				index++;
			}
			while(index < game_v->res_h_nu)
			{
				my_mlx_pixel_put(img, x, index, game_v->floor_color->n_color);
				index++;
			}
		x++;
	}
}
*/