
#include "../libcub.h"

void texture_filler(t_texture *texture, t_window *window, char *text_name)
{
texture->img = mlx_xpm_file_to_image(window->mlx, text_name, &texture->img_width,
												&texture->img_height);
texture->addr = (int *)mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
													&texture->line_length, &texture->endian);
}

void textures_filler(t_window *window)
{
	texture_filler(window->textuures->n_texture, window, window->game_v->no_texture);
	texture_filler(window->textuures->s_textture, window, window->game_v->so_texture);
	texture_filler(window->textuures->w_texture, window, window->game_v->we_texture);
	texture_filler(window->textuures->e_texture, window, window->game_v->ea_texture);
	texture_filler(window->textuures->sprite_texture, window, window->game_v->sprite_texture);
	if (window->game_v->skybox)
		texture_filler(window->textuures->skybox, window, window->game_v->skybox);
}