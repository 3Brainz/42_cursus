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

typedef struct	s_map
{
	char		*res_w;
	char		*res_h;
	char		*no_texture;
	char		*so_texture;
	char		*ea_texture;
	char		*we_texture;
	char		*sprite_texture;
	char		*floor_color;
	char		*ceiling_color;
	char		**map;
}				t_map;

void	map_cleaner(t_map *map);
void	map_filler(t_map *map, char *file_path);

#endif