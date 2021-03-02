/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:45:16 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/27 11:45:17 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCUB_H
# define LIBCUB_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

/*
** Structures
*/

typedef struct	s_color
{
	char		*red;
	char		*blue;
	char		*green;
}				t_color;

typedef struct	s_map
{
	char		*res_w;
	char		*res_h;
	char		*no_texture;
	char		*so_texture;
	char		*ea_texture;
	char		*we_texture;
	char		*sprite_texture;
	t_color		floor_color;
	t_color		ceiling_color;
	char		**map;
}				t_map;

/*
** String_utilities
*/

int		ft_numlen(char **str);
void	ft_jump_spaces(char **str);

/*
** Map_utils_functions
*/

void	map_cleaner(t_map *map);
void	color_cleaner(t_color *color);
char	*take_value_s_cub_parser(char **str, int offset);
void	fill_color(char **str, int offset, t_color *color);

/*
** Map_reader_functions
*/

int		map_filler(t_map *map, char *file_path);

#endif