#include "../libcub.h"

void	game_v_cleaner(t_game_v *game_v)
{
	game_v->res_w = 0;
	game_v->res_h = 0;
	game_v->res_w_nu = 0;
	game_v->res_h_nu = 0;
	game_v->no_texture = 0;
	game_v->so_texture = 0;
	game_v->ea_texture = 0;
	game_v->we_texture = 0;
	game_v->sprite_texture = 0;
	color_cleaner(game_v->ceiling_color);
	color_cleaner(game_v->floor_color);
	game_v->map = 0;
	game_v->s_cords = 0;
	game_v->s_count = 0;
}

void	color_cleaner(t_color *color)
{
	color->red = 0;
	color->blue = 0;
	color->green = 0;
}

void	plane_cleaner(t_plane *plane)
{
	plane->dir_x = 0;
	plane->dir_y = 0;
	plane->plane_x = 0;
	plane->plane_y = 0;
}

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
