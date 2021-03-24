
void	cast_ray(t_player *player, t_game_v *game_v, t_data *img, t_window *window)
{
	float zbuffer[3000];
	ft_bzero(zbuffer, 3000);
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
						my_mlx_pixel_put(img, x, index, window->textuures->e_texture->addr[texHeight * texY + texX]);
					else
						my_mlx_pixel_put(img, x, index, window->textuures->w_texture->addr[texHeight * texY + texX]);
				}
				else
				{
					if (rayDirY > 0)
						my_mlx_pixel_put(img, x, index, window->textuures->s_textture->addr[texHeight * texY + texX]);
					else
						my_mlx_pixel_put(img, x, index,window->textuures->n_texture->addr[texHeight * texY + texX]);
				}
				index++;
			}
			while(index < game_v->res_h_nu)
			{
				my_mlx_pixel_put(img, x, index, game_v->floor_color->n_color);
				index++;
			}
		zbuffer[x] = perpWallDist;
		x++;
	}

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
			if(transformY > 0 && stripe > 0 && stripe < game_v->res_w_nu && transformY < zbuffer[stripe])
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
		/*
		for(int i = 0; i < game_v->s_count; i++)
		{
		//translate sprite position to relative to camera
		t_coords sprite;

		sprite = game_v->s_cords[i];
		double spriteY = sprite.y - player->pos_y;
		double spriteX = sprite.x - player->pos_x;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (player->plane->plane_x * player->plane->dir_y - player->plane->dir_x * player->plane->plane_y); //required for correct matrix multiplication

		double transformX = invDet * (player->plane->dir_y * spriteX - player->plane->dir_x * spriteY);
		double transformY = invDet * (-player->plane->plane_y * spriteX + player->plane->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((game_v->res_w_nu / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(game_v->res_h_nu / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + game_v->res_h_nu / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + game_v->res_h_nu / 2 + vMoveScreen;
		if(drawEndY >= game_v->res_h_nu) drawEndY = game_v->res_h_nu - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(game_v->res_h_nu / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= game_v->res_w_nu) drawEndX = game_v->res_w_nu - 1;

		//loop through every vertical stripe of the sprite on screen
		
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(128 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 128;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
			int d = (y - vMoveScreen) * 128 - game_v->res_h_nu * 64 + spriteHeight * 64; //256 and 128 factors to avoid floats
			//int texY = ((d * texHeight) / spriteHeight) / 256;
			my_mlx_pixel_put(img, stripe, y, window->textuures->n_texture->addr[texX + d]);
			}
		}
	}*/
}
