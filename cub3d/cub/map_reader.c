/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:26:58 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/01 11:26:59 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

/*
**typedef struct	s_map
**{
**	char		*res_w;
**	char		*res_h;
**	char		*no_texture;
**	char		*so_texture;
**	char		*ea_texture;
**	char		*we_texture;
**	char		*sprite_texture;
**	char		*floor_color;
**	char		*ceiling_color;
**	char		**map;
**}				t_map;
*/

static void	line_texture_analizer(char *str, t_map *map)
{
	ft_jump_spaces(&str);
	if (*str == 'N' && str[1] == 'O')
		map->no_texture = take_value_s_cub_parser(&str, 2);
	else if (*str == 'S' && str[1] == 'O')
		map->so_texture = take_value_s_cub_parser(&str, 2);
	else if (*str == 'W' && str[1] == 'E')
		map->we_texture = take_value_s_cub_parser(&str, 2);
	else if (*str == 'E' && str[1] == 'A')
		map->ea_texture = take_value_s_cub_parser(&str, 2);
	else if (*str == 'S')
		map->sprite_texture = take_value_s_cub_parser(&str, 1);
}

static void	line_measures_analizer(char *str, t_map *map)
{
	ft_jump_spaces(&str);
	if (*str == 'R')
	{
		str++;
		ft_jump_spaces(&str);
		if (ft_isdigit(*str))
			map->res_w = ft_substr(str, 0, ft_numlen(&str));
		else
			return ;
		ft_jump_spaces(&str);
		if (ft_isdigit(*str))
			map->res_h = ft_substr(str, 0, ft_numlen(&str));
		else
			return ;
	}
}

static void	line_colors_analizer(char *str, t_map *map)
{
	ft_jump_spaces(&str);
	if (*str == 'C')
		fill_color(&str, 1, &map->ceiling_color);
	else if (*str == 'F')
		fill_color(&str, 1, &map->floor_color);
}

int			map_filler(t_map *map, char *file_path)
{
	int		map_fd;
	char	*line;

	line = 0;
	map->res_h = 0;
	map_fd = open(file_path, 00);
	while (get_next_line(map_fd, &line))
	{
		line_texture_analizer(line, map);
		line_measures_analizer(line, map);
		line_colors_analizer(line, map);
		free(line);
	}
	return (0);
}
