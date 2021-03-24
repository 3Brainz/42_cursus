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

void	sprite_caster(t_player *player, t_game_v *game_v, t_data *img, t_window *window);

void	cast_ray(t_player *player, t_game_v *game_v, t_data *img, t_window *window)
{
	t_caster *caster;
	int x;

	x = 0;
	caster = player->caster;
	zero_caster(caster);
	caster->z_buffer = ft_calloc(sizeof(float), game_v->res_w_nu + 1);
	while (x < game_v->res_w_nu)
	{
		zero_caster(caster);
		ray_pos_and_dir(caster, game_v, player, x);
		ray_collider(caster, player);
		ray_dda(caster, game_v);
		line_measure_dist(caster, game_v, player);
		texturer(caster, player, game_v, window);
		ver_line(x, caster, window, img);
		caster->z_buffer[x] = caster->perpWallDist;
		x++;
	}
	sprite_caster(player, game_v, img, window);
	free(caster->z_buffer);
}
void	sprite_positioner(t_player *player, t_game_v *game_v, t_window *window)
{
	t_s_caster *s_caster;

	s_caster = player->caster->sprite_caster;
	s_caster->spriteX = game_v->s_cords[i].x - player->pos_x;
	s_caster->spriteY = game_v->s_cords[i].y - player->pos_y;
}

void	sprite_dimensioner(t_player *player, t_game_v *game_v, t_window *window)
{
	t_s_caster *s_caster;

	s_caster = player->caster->sprite_caster;
	s_caster->invDet = 1.0 / (player->plane->plane_x * player->plane->dir_y - player->plane->dir_x * player->plane->plane_y);
	s_caster->transformX = s_caster->invDet * (player->plane->dir_y * s_caster->spriteX - player->plane->dir_x * s_caster->spriteY);
	s_caster->transformY = s_caster->invDet * ((-player->plane->plane_y) * s_caster->spriteX + player->plane->plane_x * s_caster->spriteY);
	s_caster->spriteScreenX = game_v->res_w_nu - (int)((game_v->res_w_nu / 2) * (1 + s_caster->transformX / s_caster->transformY));
	s_caster->vMoveScreen = (int)(0.0 / s_caster->transformY);
	s_caster->spriteHeight = (abs((int)(game_v->res_h_nu / s_caster->transformY))) / 1; 
}

void	sprite_painting_coords(t_player *player, t_game_v *game_v, t_window *window)
{
	
}
void	sprite_caster(t_player *player, t_game_v *game_v, t_data *img, t_window *window)
{
	t_caster *caster;
	caster = player->caster;
	sprite_sorter(game_v->s_cords, player, game_v);
		for(int i = 0; i < game_v->s_count; i++)
		{
			double spriteX = game_v->s_cords[i].x - player->pos_x;
      		double spriteY = game_v->s_cords[i].y - player->pos_y;
			double invDet = 1.0 / (player->plane->plane_x * player->plane->dir_y - player->plane->dir_x * player->plane->plane_y); //required for correct matrix multiplication
			double transformX = invDet * (player->plane->dir_y * spriteX - player->plane->dir_x * spriteY);
			double transformY = invDet * ((-player->plane->plane_y) * spriteX + player->plane->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
			int spriteScreenX = game_v->res_w_nu - (int)((game_v->res_w_nu / 2) * (1 + transformX / transformY));
			#define uDiv 1
			#define vDiv 1
			#define vMove 0.0
			int vMoveScreen = (int)(vMove / transformY);
			int spriteHeight = (abs((int)(game_v->res_h_nu / transformY))) / vDiv; 

			int drawStartY = -spriteHeight / 2 + game_v->res_h_nu / 2 + vMoveScreen;
			if(drawStartY < 0) 
				drawStartY = 0;
			int drawEndY = spriteHeight / 2 + game_v->res_h_nu / 2 + vMoveScreen;
			if(drawEndY >= game_v->res_h_nu) 
				drawEndY = game_v->res_h_nu - 1;
			//calculate width of the sprite
			int spriteWidth = (abs((int)(game_v->res_h_nu / transformY))) / uDiv;
			int drawStartX = -spriteWidth / 2 + spriteScreenX;
			if(drawStartX < 0) 
				drawStartX = 0;
			int drawEndX = spriteWidth / 2 + spriteScreenX;
			if(drawEndX >= game_v->res_w_nu) 
				drawEndX = game_v->res_w_nu - 1;
			for(int stripe = drawStartX; stripe < drawEndX; stripe++)
			{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * window->textuures->w_texture->img_width / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < game_v->res_w_nu && transformY < caster->z_buffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y-vMoveScreen) * 256 - game_v->res_h_nu * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * window->textuures->w_texture->img_height) / spriteHeight) / 256;
					unsigned  int color = (unsigned int)window->textuures->w_texture->addr[window->textuures->w_texture->img_width * texY + texX]; //get current color from the texture
					//color = 0xFFFFFFF;
					if((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(img, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
				}
			}
		}
}
