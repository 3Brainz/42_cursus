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
typedef struct	s_map
{
	int			res_w;
	int			res_h;
	char		*no_texture;
	char		*so_texture;
	char		*ea_texture;
	char		*we_texture;
	char		*sprite_texture;
	int			floor_color;
	int			ceiling_color;
	int			**map;
}				t_map;
*/

void	map_cleaner(t_map *map)
{
	map->res_w = 0;
	map->res_h = 0;
	map->no_texture = 0;
	map->so_texture = 0;
	map->ea_texture = 0;
	map->we_texture = 0;
	map->sprite_texture = 0;
	map->floor_color = 0;
	map->ceiling_color = 0;
	map->map = 0;
}

int ft_numlen(char **str)
{
	int index;

	index = 0;
	while(ft_isdigit(**str))
	{
		*str += 1;
		index++;
	}
	return (index);
}

void ft_jump_spaces(char **str)
{
	while (**str == ' ' && **str)
		*str += 1;
}

void line_texture_analizer(char *str, t_map *map)
{
	ft_jump_spaces(&str);
	if (*str == 'N' && *str + 1 == 'O')
	{
		str += 2;
		ft_jump_spaces(&str);
		map->no_texture = ft_strdup(str);
	}
	else if (*str == 'S' && *str + 1 == 'O')
	{
		str += 2;
		ft_jump_spaces(&str);
		map->so_texture = ft_strdup(str);
	}
	else if (*str == 'W' && *str + 1 == 'E')
	{
		str += 2;
		ft_jump_spaces(&str);
		map->we_texture = ft_strdup(str);
	}
	else if (*str == 'E' && *str + 1 == 'A')
	{
		str += 2;
		ft_jump_spaces(&str);
		map->ea_texture = ft_strdup(str);
	}
	else if (*str == 'S')
	{
		str += 1;
		ft_jump_spaces(&str);
		map->sprite_texture = ft_strdup(str);
	}
}

void line_measures_analizer(char *str, t_map *map)
{
	ft_jump_spaces(&str);
	if (*str == 'R')
	{
		str++;
		ft_jump_spaces(&str);
		map->res_w = ft_substr(str, 0, ft_numlen(&str));
		ft_jump_spaces(&str);
		map->res_h = ft_substr(str, 0, ft_numlen(&str));
	}
}

void	map_filler(t_map *map, char *file_path)
{
	int map_fd;
	char *line =0;
	map->res_h = 0;
	map_fd = open(file_path, 00);
	while (get_next_line(map_fd, &line))
	{
		line_texture_analizer(line, map);
		line_measures_analizer(line, map);
		free(line);
	}
	return ;
}
