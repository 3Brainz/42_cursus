
void	cast_ray(t_player *player, t_game_v *game_v, t_data *img, t_window *window)
{
	float zbuffer[3000];
	ft_bzero(zbuffer, 3000);
	int x = 0;
	while (x < game_v->res_w_nu)
	{
		//calculate ray position and direction
		double camera_x = 2 * x / (double)game_v->res_w_nu - 1; //x-coordinate in camera space
		double ray_dir_x = player->plane->dir_x - player->plane->plane_x * camera_x;
		double ray_dir_y = player->plane->dir_y - player->plane->plane_y * camera_x;
		//which box of the map we're in
		int map_x = (int)(player->pos_x);
		int map_y = (int)(player->pos_y);

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;

		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player->pos_x) * delta_dist_x;
		}
		if(ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player->pos_y) * delta_dist_y;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(side_dist_x < side_dist_y)
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
			//Check if ray has hit a wall
			if(game_v->map[map_y][map_x] == '1') hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) perp_wall_dist = (map_x - player->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else          perp_wall_dist = (map_y - player->pos_y + (1 - step_y) / 2) / ray_dir_y;

		//Calculate height of line to draw on screen
		int line_height = (int)(game_v->res_h_nu / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int draw_start = -line_height / 2 + game_v->res_h_nu / 2;
		if(draw_start < 0)draw_start = 0;
		int draw_end = line_height / 2 + game_v->res_h_nu / 2;
		if(draw_end >= game_v->res_h_nu || draw_end < 0)draw_end = game_v->res_h_nu - 1;

//--------------------------------------------------------------------------------------//----------//------
		double wall_x; //where exactly the wall was hit
			if(side == 0)	
			wall_x = player->pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = player->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor((wall_x));
		//x coordinate on the texture
		int tex_x = (int)(wall_x * (double)(texWidth));
		if(side == 0 && ray_dir_x > 0)
			tex_x = texWidth - tex_x - 1;
		if(side == 1 && ray_dir_y < 0)
			tex_x = texWidth - tex_x - 1;
		double step = 1.0 * texHeight / line_height;
		double tex_pos = (draw_start - game_v->res_h_nu / 2 + line_height / 2) * step;

		//choose wall color
		// int color = 0x00FF0000;
		//give x and y sides different brightness
		//if(side == 1) {color = color / 2;}
		//draw the pixels of the stripe as a vertical line
		//ver_line(x, draw_start, draw_end, game_v, img);
		int index;

		index = 0;

		while (index <= draw_start)
			{
				my_mlx_pixel_put(img, x, index, game_v->ceiling_color->n_color);
				index++;
			}
			while(index <= draw_end)
			{
				int tex_y = (int)tex_pos & (texHeight - 1);
        		tex_pos += step;
				if (side == 0)
				{
					if (ray_dir_x > 0)
						my_mlx_pixel_put(img, x, index, window->textuures->e_texture->addr[texHeight * tex_y + tex_x]);
					else
						my_mlx_pixel_put(img, x, index, window->textuures->w_texture->addr[texHeight * tex_y + tex_x]);
				}
				else
				{
					if (ray_dir_y > 0)
						my_mlx_pixel_put(img, x, index, window->textuures->s_textture->addr[texHeight * tex_y + tex_x]);
					else
						my_mlx_pixel_put(img, x, index,window->textuures->n_texture->addr[texHeight * tex_y + tex_x]);
				}
				index++;
			}
			while(index < game_v->res_h_nu)
			{
				my_mlx_pixel_put(img, x, index, game_v->floor_color->n_color);
				index++;
			}
		zbuffer[x] = perp_wall_dist;
		x++;
	}

		sprite_sorter(game_v->s_cords, player, game_v);
		for(int i = 0; i < game_v->s_count; i++)
		{
			double sprite_x = game_v->s_cords[i].x - player->pos_x;
      		double sprite_y = game_v->s_cords[i].y - player->pos_y;
			double inv_det = 1.0 / (player->plane->plane_x * player->plane->dir_y - player->plane->dir_x * player->plane->plane_y); //required for correct matrix multiplication
			double transform_x = inv_det * (player->plane->dir_y * sprite_x - player->plane->dir_x * sprite_y);
			double transform_y = inv_det * ((-player->plane->plane_y) * sprite_x + player->plane->plane_x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D
			int sprite_screen_x = game_v->res_w_nu - (int)((game_v->res_w_nu / 2) * (1 + transform_x / transform_y));
			#define uDiv 1
			#define vDiv 1
			#define vMove 0.0
			int v_move_screen = (int)(vMove / transform_y);
			int sprite_height = (abs((int)(game_v->res_h_nu / transform_y))) / vDiv; 

			int draw_start_y = -sprite_height / 2 + game_v->res_h_nu / 2 + v_move_screen;
			if(draw_start_y < 0) 
				draw_start_y = 0;
			int draw_end_y = sprite_height / 2 + game_v->res_h_nu / 2 + v_move_screen;
			if(draw_end_y >= game_v->res_h_nu) 
				draw_end_y = game_v->res_h_nu - 1;
			//calculate width of the sprite
			int sprite_width = (abs((int)(game_v->res_h_nu / transform_y))) / uDiv;
			int draw_start_x = -sprite_width / 2 + sprite_screen_x;
			if(draw_start_x < 0) 
				draw_start_x = 0;
			int draw_end_x = sprite_width / 2 + sprite_screen_x;
			if(draw_end_x >= game_v->res_w_nu) 
				draw_end_x = game_v->res_w_nu - 1;
			for(int stripe = draw_start_x; stripe < draw_end_x; stripe++)
			{
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * window->textuures->w_texture->img_width / sprite_width) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transform_y > 0 && stripe > 0 && stripe < game_v->res_w_nu && transform_y < zbuffer[stripe])
				for(int y = draw_start_y; y < draw_end_y; y++) //for every pixel of the current stripe
				{
					int d = (y-v_move_screen) * 256 - game_v->res_h_nu * 128 + sprite_height * 128; //256 and 128 factors to avoid floats
					int tex_y = ((d * window->textuures->w_texture->img_height) / sprite_height) / 256;
					unsigned  int color = (unsigned int)window->textuures->w_texture->addr[window->textuures->w_texture->img_width * tex_y + tex_x]; //get current color from the texture
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
		double sprite_y = sprite.y - player->pos_y;
		double sprite_x = sprite.x - player->pos_x;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double inv_det = 1.0 / (player->plane->plane_x * player->plane->dir_y - player->plane->dir_x * player->plane->plane_y); //required for correct matrix multiplication

		double transform_x = inv_det * (player->plane->dir_y * sprite_x - player->plane->dir_x * sprite_y);
		double transform_y = inv_det * (-player->plane->plane_y * sprite_x + player->plane->plane_x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int sprite_screen_x = (int)((game_v->res_w_nu / 2) * (1 + transform_x / transform_y));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int v_move_screen = (int)(vMove / transform_y);

		//calculate height of the sprite on screen
		int sprite_height = abs((int)(game_v->res_h_nu / (transform_y))) / vDiv; //using "transform_y" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int draw_start_y = -sprite_height / 2 + game_v->res_h_nu / 2 + v_move_screen;
		if(draw_start_y < 0) draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + game_v->res_h_nu / 2 + v_move_screen;
		if(draw_end_y >= game_v->res_h_nu) draw_end_y = game_v->res_h_nu - 1;

		//calculate width of the sprite
		int sprite_width = abs((int)(game_v->res_h_nu / (transform_y))) / uDiv;
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if(draw_start_x < 0) draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if(draw_end_x >= game_v->res_w_nu) draw_end_x = game_v->res_w_nu - 1;

		//loop through every vertical stripe of the sprite on screen
		
		for(int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			int tex_x = (int)(128 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * texWidth / sprite_width) / 128;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			for(int y = draw_start_y; y < draw_end_y; y++) //for every pixel of the current stripe
			{
			int d = (y - v_move_screen) * 128 - game_v->res_h_nu * 64 + sprite_height * 64; //256 and 128 factors to avoid floats
			//int tex_y = ((d * texHeight) / sprite_height) / 256;
			my_mlx_pixel_put(img, stripe, y, window->textuures->n_texture->addr[tex_x + d]);
			}
		}
	}*/
}
