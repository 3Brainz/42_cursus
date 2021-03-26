/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:04:04 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/26 16:04:06 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void		cast_ray(t_player *player, t_game_v *game_v,
						t_data *img, t_window *window)
{
	t_caster	*caster;
	int			x;

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

void		sprite_caster(t_player *player, t_game_v *game_v,
							t_data *img, t_window *window)
{
	int			s_index;
	t_caster	*caster;

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
