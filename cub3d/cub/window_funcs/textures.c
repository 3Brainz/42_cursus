/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:37:49 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/25 18:37:51 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libcub.h"

void	texture_filler(t_texture *texture, t_window *window, char *text_name)
{
	texture->img = mlx_xpm_file_to_image(window->mlx, text_name,
									&texture->img_width, &texture->img_height);
	texture->addr = (int *)mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

void	textures_filler(t_window *window)
{
	t_game_v *game_v;

	game_v = window->game_v;
	texture_filler(window->textuures->n_texture, window, game_v->no_texture);
	texture_filler(window->textuures->s_textture, window, game_v->so_texture);
	texture_filler(window->textuures->w_texture, window, game_v->we_texture);
	texture_filler(window->textuures->e_texture, window, game_v->ea_texture);
	texture_filler(window->textuures->sprite_texture, window,
					game_v->sprite_texture);
	if (window->game_v->skybox)
		texture_filler(window->textuures->skybox, window, game_v->skybox);
}
