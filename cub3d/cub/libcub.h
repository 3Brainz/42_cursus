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
# include <stdarg.h>
# include <mlx.h>
# define MAP_SPACE_VAL 0

# define W_CODE 13
# define A_CODE 0
# define S_CODE 1
# define D_CODE 2
# define L_A_CODE 123
# define R_A_CODE 124
# define L_BUTTON 1
# define R_BUTTON 2

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
	int			res_w_nu;
	int			res_h_nu;
	char		*no_texture;
	char		*so_texture;
	char		*ea_texture;
	char		*we_texture;
	char		*sprite_texture;
	t_color		floor_color[1];
	t_color		ceiling_color[1];
	char		**map;
}				t_game_v;

/*
**Structures mlx
*/

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_mouse_ck{
	int			button;
	int			pos_x;
	int			pos_y;
}				t_mouse_ck;


typedef struct s_mouse_pos{
	int			pos_x;
	int			pos_y;
}				t_mouse_pos;

typedef struct s_keys{
int				w_key;
int				a_key;
int				s_key;
int				d_key;
int				left_arrow;
int				right_arrow;
int				esc;
}				t_keys;

typedef struct 	s_window{
	void		*mlx;
	void		*mlx_win;
	t_data		curr_img[1];
	t_mouse_ck	click[1];
	t_mouse_pos	mouse_pos[1];
	t_keys		keys[1];
	int			close;
	t_game_v	*game_v;
}				t_window;

/*
**Player_structs
*/

typedef struct	s_player{
float			pos_x;
float			pos_y;
}				t_player;

/*
** String_utilities
*/

int				ft_numlen(char **str);
void			ft_jump_spaces(char **str);
char			*ft_strjoin_new_line(char const *s1, char const *s2);
void			change_char_in_s(char *str, char dest, char substitute);
void			free_mat(void **mat);

/*
**Gen_utils
*/

void			initialize_vars(int vars_number, ...);
void			free_if_exists(void **var);

/*
** Game_v_utils_functions
*/

void			game_v_cleaner(t_game_v *game_v);
void			color_cleaner(t_color *color);
char			*take_value_s_cub_parser(char **str, int offset);
void			fill_color(char **str, int offset, t_color *color);
void			free_game_v(t_game_v *game_v);

/*
** Game_v_checks
*/

int				is_color_filled(t_color *color);
int 	is_map_moment(t_game_v *game_v);
int		are_game_v_ok(t_game_v *game_v);

/*
** Map_filler
*/

void			print_mat(char **mat);
void			copy_mat(char **dest, char **src);
size_t			mat_len(char **mat);
void			add_string_to_mat(char ***mat, char *str);

/*
**Map_c
*/

int				is_map_valid(char **map);

/*
** game_v_reader_functions
*/

int				game_v_filler(t_game_v *game_v, char *file_path);

/*
**Win_func
*/

void			start_win(t_window *window, t_game_v *game_v);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			new_image(t_data *image, t_window *window, int width, int height);

/*
**Mouse funks
*/

int				mouse_click(int button, int pos_x,int pos_y, t_window *window);
void			mouse_click_print(t_mouse_ck *click);
int				mouse_pos_mov(int x, int y, t_window *window);

/*
**Structs_funcs
*/

void			clean_data(t_data *data);
void			clean_mouse_pos(t_mouse_pos *mouse_pos);
void			clean_mouse_click(t_mouse_ck *click);
void			clean_window_struct(t_window *window);
void			clean_keys(t_keys *keys);

/*
**Keyboard_funcs
*/

int				key_hook_in(int keycode, t_window *window);
int				key_hook_out(int keycode, t_window *window);

/*
**Minimap
*/

void			add_minimap_to_img(t_data *image, t_game_v *game_v, int factor);

#endif
