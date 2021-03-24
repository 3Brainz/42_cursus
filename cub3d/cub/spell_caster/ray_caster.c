#include "../libcub.h"

void	zero_caster(t_caster *caster)
{
	caster->camera_x = 0;
	caster->ray_dir_x = 0;
	caster->ray_dir_y = 0;
	caster->map_x = 0;
	caster->map_y = 0;
	caster->side_dist_x = 0;
	caster->side_dist_y = 0;
	caster->delta_dist_x = 0;
	caster->delta_dist_y = 0;
	caster->perp_wall_dist = 0;
	caster->step_x = 0;
	caster->step_y = 0;
	caster->hit = 0;
	caster->side = 0;
	caster->line_height = 0;
	caster->draw_start = 0;
	caster->draw_end = 0;
	caster->wall_x = 0;
	caster->tex_x = 0;
	caster->step = 0;
	caster->tex_pos = 0;
	caster->tex_y = 0;
}

void	zero_s_caster(t_s_caster *s_caster)
{
	s_caster->sprite_x = 0;
	s_caster->sprite_y = 0;
	s_caster->inv_det = 0;
	s_caster->transform_x = 0;
	s_caster->transform_y = 0;
	s_caster->sprite_screen_x = 0;
	s_caster->v_move_screen = 0;
	s_caster->sprite_height = 0;
	s_caster->draw_start_y = 0;
	s_caster->draw_end_y = 0;
	s_caster->sprite_width = 0;
	s_caster->draw_start_x = 0;
	s_caster->draw_end_x = 0;
	s_caster->tex_x = 0;
	s_caster->d = 0;
	s_caster->tex_y = 0;
}

void	ray_pos_and_dir(t_caster *caster, t_game_v *game_v,t_player *player, int x)
{
	caster->camera_x = 2 * x / (double)game_v->res_w_nu - 1;
	caster->ray_dir_x = player->plane->dir_x - player->plane->plane_x * caster->camera_x;
	caster->ray_dir_y = player->plane->dir_y - player->plane->plane_y * caster->camera_x;
	caster->map_x = (int)(player->pos_x);
	caster->map_y = (int)(player->pos_y);
	caster->delta_dist_x = fabs(1 / caster->ray_dir_x);
	caster->delta_dist_y = fabs(1 / caster->ray_dir_y);
}

void	ray_collider(t_caster *caster, t_player *player)
{
	caster->hit = 0;
	if(caster->ray_dir_x < 0)
	{
		caster->step_x = -1;
		caster->side_dist_x = (player->pos_x - caster->map_x) * caster->delta_dist_x;
	}
	else
	{
		caster->step_x = 1;
		caster->side_dist_x = (caster->map_x + 1.0 - player->pos_x) * caster->delta_dist_x;
	}
	if(caster->ray_dir_y < 0)
	{
		caster->step_y = -1;
		caster->side_dist_y = (player->pos_y - caster->map_y) * caster->delta_dist_y;
	}
	else
	{
		caster->step_y = 1;
		caster->side_dist_y = (caster->map_y + 1.0 - player->pos_y) * caster->delta_dist_y;
	}
}

void	ray_dda(t_caster *caster, t_game_v *game_v)
{
	while (caster->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(caster->side_dist_x < caster->side_dist_y)
			{
				caster->side_dist_x += caster->delta_dist_x;
				caster->map_x += caster->step_x;
				caster->side = 0;
			}
			else
			{
				caster->side_dist_y += caster->delta_dist_y;
				caster->map_y += caster->step_y;
				caster->side = 1;
			}
			//Check if ray has hit a wall
			if(game_v->map[caster->map_y][caster->map_x] == '1') 
				caster->hit = 1;
		}
}

void	line_measure_dist(t_caster *caster, t_game_v *game_v, t_player *player)
{
	if(caster->side == 0)
		caster->perp_wall_dist = (caster->map_x - player->pos_x + (1 - caster->step_x) / 2) / caster->ray_dir_x;
	else	
		caster->perp_wall_dist = (caster->map_y - player->pos_y + (1 - caster->step_y) / 2) / caster->ray_dir_y;
	caster->line_height = (int)(game_v->res_h_nu / caster->perp_wall_dist);
	caster->draw_start = -caster->line_height / 2 + game_v->res_h_nu / 2;
	if(caster->draw_start < 0)
		caster->draw_start = 0;
	caster->draw_end = caster->line_height / 2 + game_v->res_h_nu / 2;
	if(caster->draw_end >= game_v->res_h_nu || caster->draw_end < 0)
		caster->draw_end = game_v->res_h_nu - 1;
}

t_texture *texture_selector(t_window *window, t_caster *caster)
{
	if (caster->side == 0)
		{
			if (caster->ray_dir_x > 0)
				return (window->textuures->e_texture);
			else
				return (window->textuures->w_texture);
		}
		else
		{
			if (caster->ray_dir_y > 0)
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
		caster->wall_x = player->pos_y + caster->perp_wall_dist * caster->ray_dir_y;
	else
		caster->wall_x = player->pos_x + caster->perp_wall_dist * caster->ray_dir_x;
	caster->wall_x -= floor((caster->wall_x));
	//x coordinate on the texture
	caster->tex_x = (int)(caster->wall_x * (double)(texture->img_width));
	if(caster->side == 0 && caster->ray_dir_x > 0)
		caster->tex_x = texture->img_width - caster->tex_x - 1;
	if(caster->side == 1 && caster->ray_dir_y < 0)
		caster->tex_x = texture->img_width - caster->tex_x - 1;
	caster->step = 1.0 * texture->img_height / caster->line_height;
	caster->tex_pos = (caster->draw_start - game_v->res_h_nu / 2 + caster->line_height / 2) * caster->step;
}

void	ver_line(int x, t_caster *caster, t_window *window, t_data *img)
{
	int index;
	t_texture *texture;
	t_texture *skybox;
	index = 0;
	while (++index < caster->draw_start)
		if(!window->game_v->skybox)
			my_mlx_pixel_put(img, x, index, window->game_v->ceiling_color->n_color);
		else
		{
			skybox = window->textuures->skybox;
			my_mlx_pixel_put(img, x, index, skybox->addr[(int)(window->player->inclination * skybox->img_width) + index * skybox->img_width + x]);
		}
	while(++index < caster->draw_end)
	{
		caster->tex_y = (int)caster->tex_pos & (texture->img_height - 1);
		caster->tex_pos += caster->step;
		texture = texture_selector(window, caster);
		my_mlx_pixel_put(img, x, index, texture->addr[texture->img_height * caster->tex_y + caster->tex_x]);
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
		caster->z_buffer[x] = caster->perp_wall_dist;
		x++;
	}
	sprite_caster(player, game_v, img, window);
	free(caster->z_buffer);
}
void	sprite_positioner(t_player *player, t_game_v *game_v, int i)
{
	t_s_caster *s_caster;

	s_caster = player->caster->sprite_caster;
	s_caster->sprite_x = game_v->s_cords[i].x - player->pos_x;
	s_caster->sprite_y = game_v->s_cords[i].y - player->pos_y;
}

void	sprite_dimensioner(t_player *player, t_game_v *game_v)
{
	t_s_caster *s_caster;

	s_caster = player->caster->sprite_caster;
	s_caster->inv_det = 1.0 / (player->plane->plane_x * player->plane->dir_y - player->plane->dir_x * player->plane->plane_y);
	s_caster->transform_x = s_caster->inv_det * (player->plane->dir_y * s_caster->sprite_x - player->plane->dir_x * s_caster->sprite_y);
	s_caster->transform_y = s_caster->inv_det * ((-player->plane->plane_y) * s_caster->sprite_x + player->plane->plane_x * s_caster->sprite_y);
	s_caster->sprite_screen_x = game_v->res_w_nu - (int)((game_v->res_w_nu / 2) * (1 + s_caster->transform_x / s_caster->transform_y));
	s_caster->v_move_screen = (int)(0.0 / s_caster->transform_y);
	s_caster->sprite_height = (abs((int)(game_v->res_h_nu / s_caster->transform_y))) / 1; 
}

void	sprite_painting_coords_y(t_player *player, t_game_v *game_v)
{
	t_s_caster *s_caster;

	s_caster = player->caster->sprite_caster;
	s_caster->draw_start_y = -s_caster->sprite_height / 2 + game_v->res_h_nu / 2 + s_caster->v_move_screen;
	if(s_caster->draw_start_y < 0)
		s_caster->draw_start_y = 0;
	s_caster->draw_end_y = s_caster->sprite_height / 2 + game_v->res_h_nu / 2 + s_caster->v_move_screen;
	if(s_caster->draw_end_y >= game_v->res_h_nu)
		s_caster->draw_end_y = game_v->res_h_nu - 1;
	
}

void	sprite_painting_coords_x(t_player *player, t_game_v *game_v)
{
	t_s_caster *s_caster;

	s_caster = player->caster->sprite_caster;
	s_caster->sprite_width = (abs((int)(game_v->res_h_nu / s_caster->transform_y))) / 1;
	s_caster->draw_start_x = -s_caster->sprite_width / 2 + s_caster->sprite_screen_x;
	if(s_caster->draw_start_x < 0) 
		s_caster->draw_start_x = 0;
	s_caster->draw_end_x = s_caster->sprite_width / 2 + s_caster->sprite_screen_x;
	if(s_caster->draw_end_y >= game_v->res_w_nu) 
		s_caster->draw_end_x = game_v->res_w_nu - 1;
}
 
void	sprite_ver_line(int stripe, t_game_v *game_v, t_data *img, t_window *window)
{
	t_s_caster *s_caster;
	unsigned int color;
	int y;

	s_caster = window->player->caster->sprite_caster;
	y = s_caster->draw_start_y;
	while (y < s_caster->draw_end_y)
	{
		s_caster->d = (y-s_caster->v_move_screen) * 256 - game_v->res_h_nu * 128 + s_caster->sprite_height * 128;
		s_caster->tex_y = ((s_caster->d * window->textuures->w_texture->img_height) / s_caster->sprite_height) / 256;
		color = (unsigned int)window->textuures->w_texture->addr[window->textuures->w_texture->img_width * s_caster->tex_y + s_caster->tex_x];
		if((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(img, stripe, y, color);
		y++;
	}
}

void	sprite_print(t_player *player, t_game_v *game_v, t_data *img, t_window *window)
{
	int	stripe;
	t_s_caster *s_caster;

	s_caster = player->caster->sprite_caster;
	stripe = s_caster->draw_start_x;
	while (stripe < s_caster->draw_end_x)
	{
		s_caster->tex_x = (int)(256 * (stripe - (-s_caster->sprite_width / 2 + s_caster->sprite_screen_x)) * window->textuures->w_texture->img_width / s_caster->sprite_width) / 256;
		if(s_caster->transform_y > 0 && stripe > 0 && stripe < game_v->res_w_nu && s_caster->transform_y < player->caster->z_buffer[stripe])
			sprite_ver_line(stripe, game_v, img, window);
		stripe++;
	}	
}

void	sprite_caster(t_player *player, t_game_v *game_v, t_data *img, t_window *window)
{
	int s_index;
	t_caster *caster;

	caster = player->caster;
	s_index = 0;
	sprite_sorter(game_v->s_cords, player, game_v);
	while (s_index < game_v->s_count)
	{
		zero_s_caster(caster->sprite_caster);
		sprite_positioner(player, game_v, s_index);
		sprite_dimensioner(player, game_v);
		sprite_painting_coords_y(player, game_v);
		sprite_painting_coords_x(player, game_v);
		sprite_print(player, game_v, img, window);
		s_index++;
	}
}
