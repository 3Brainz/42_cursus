/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_v_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:31:14 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/01 17:31:21 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void	game_v_cleaner(t_game_v *game_v)
{
	game_v->res_w = 0;
	game_v->res_h = 0;
	game_v->no_texture = 0;
	game_v->so_texture = 0;
	game_v->ea_texture = 0;
	game_v->we_texture = 0;
	game_v->sprite_texture = 0;
	color_cleaner(&game_v->ceiling_color);
	color_cleaner(&game_v->floor_color);
	game_v->map = 0;
}

void	color_cleaner(t_color *color)
{
	color->red = 0;
	color->blue = 0;
	color->green = 0;
}

char	*take_value_s_cub_parser(char **str, int offset)
{
	*str += offset;
	ft_jump_spaces(str);
	if (ft_strlen(*str))
		return (ft_strdup(*str));
	else
		return (0);
}

void	fill_color(char **str, int offset, t_color *color)
{
	*str += offset;
	ft_jump_spaces(str);
	if (ft_isdigit(**str))
		color->red = ft_substr(*str, 0, ft_numlen(str));
	if (**str == ',')
	{
		*str += 1;
		if (ft_isdigit(**str))
			color->blue = ft_substr(*str, 0, ft_numlen(str));
	}
	if (**str == ',')
	{
		*str += 1;
		if (ft_isdigit(**str))
			color->green = ft_substr(*str, 0, ft_numlen(str));
	}
}
