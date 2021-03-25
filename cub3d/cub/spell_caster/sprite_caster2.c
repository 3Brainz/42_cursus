/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_caster2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:05:55 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/25 18:23:56 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void		sprite_ver_line(int stripe, t_game_v *game_v, t_data *img,
							t_window *window)
{
	t_s_caster		*s_caster;
	t_texture		*sp_texture;
	unsigned int	color;
	int				y;

	s_caster = window->player->caster->sprite_caster;
	sp_texture = window->textuures->sprite_texture;
	y = s_caster->draw_start_y;
	while (y < s_caster->draw_end_y)
	{
		s_caster->d = (y - s_caster->v_move_screen) * 256 - game_v->res_h_nu *
						128 + s_caster->sprite_height * 128;
		s_caster->tex_y = ((s_caster->d *
						sp_texture->img_height) /
						s_caster->sprite_height) / 256;
		color = (unsigned int)sp_texture->addr[sp_texture->img_width *
						s_caster->tex_y + s_caster->tex_x];
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(img, stripe, y, color);
		y++;
	}
}

void		sprite_print(t_player *player, t_game_v *game_v, t_data *img,
							t_window *window)
{
	int			stripe;
	t_s_caster	*s_caster;
	t_texture	*sp_texture;

	sp_texture = window->textuures->sprite_texture;
	s_caster = player->caster->sprite_caster;
	stripe = s_caster->draw_start_x;
	while (stripe < s_caster->draw_end_x)
	{
		s_caster->tex_x = (int)(256 * (stripe - (-s_caster->sprite_width / 2 +
							s_caster->sprite_screen_x)) *
							sp_texture->img_width /
							s_caster->sprite_width) / 256;
		if (s_caster->transform_y > 0 && stripe > 0 && stripe < game_v->res_w_nu
			&& s_caster->transform_y < player->caster->z_buffer[stripe])
			sprite_ver_line(stripe, game_v, img, window);
		stripe++;
	}
}
