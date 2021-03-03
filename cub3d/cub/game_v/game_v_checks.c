/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_v_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:09:07 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/02 11:09:08 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

int		is_color_filled(t_color *color)
{
	if (color->red && color->green && color->blue)
		return (1);
	return (0);
}

int		is_map_moment(t_game_v *game_v)
{
	if (game_v->res_h && game_v->res_w &&
		game_v->no_texture && game_v->so_texture &&
		game_v->we_texture && game_v->ea_texture &&
		game_v->sprite_texture &&
		is_color_filled(&game_v->floor_color) &&
		is_color_filled(&game_v->ceiling_color))
		return (1);
	return (0);
}

int		are_game_v_ok(t_game_v *game_v)
{
	if(is_map_moment(game_v))
		return (1);
	return (0);
}