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
# include  <stdarg.h>
# define MAP_SPACE_VAL 0

/*
** Structures
*/

typedef struct	s_color
{
	char		*red;
	char		*blue;
	char		*green;
}				t_color;

typedef struct	s_game_v
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
}				t_game_v;

/*
** String_utilities
*/

int				ft_numlen(char **str);
void			ft_jump_spaces(char **str);
char			*ft_strjoin_new_line(char const *s1, char const *s2);
void			change_char_in_s(char *str, char dest, char substitute);

/*
**Gen_utils
*/

void			initialize_vars(int vars_number, ...);

/*
** Game_v_utils_functions
*/

void			game_v_cleaner(t_game_v *game_v);
void			color_cleaner(t_color *color);
char			*take_value_s_cub_parser(char **str, int offset);
void			fill_color(char **str, int offset, t_color *color);

/*
** Game_v_checks
*/

int				is_color_filled(t_color *color);
int 	is_map_moment(t_game_v *game_v);

/*
** Map_filler
*/

void			print_mat(char **mat);
void			copy_mat(char **dest, char **src);
size_t			mat_len(char **mat);
void			add_string_to_mat(char ***mat, char *str);

/*
** game_v_reader_functions
*/

int				game_v_filler(t_game_v *game_v, char *file_path);

#endif
