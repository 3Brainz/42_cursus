/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_v_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:26:58 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/01 11:26:59 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

static void	line_texture_analizer(char *str, t_game_v *game_v)
{
	ft_jump_spaces(&str);
	if (*str == 'N' && str[1] == 'O')
		game_v->no_texture = take_value_s_cub_parser(&str, 2);
	else if (*str == 'S' && str[1] == 'O')
		game_v->so_texture = take_value_s_cub_parser(&str, 2);
	else if (*str == 'W' && str[1] == 'E')
		game_v->we_texture = take_value_s_cub_parser(&str, 2);
	else if (*str == 'E' && str[1] == 'A')
		game_v->ea_texture = take_value_s_cub_parser(&str, 2);
	else if (*str == 'S')
		game_v->sprite_texture = take_value_s_cub_parser(&str, 1);
}

static void	line_measures_analizer(char *str, t_game_v *game_v)
{
	ft_jump_spaces(&str);
	if (*str == 'R')
	{
		str++;
		ft_jump_spaces(&str);
		if (ft_isdigit(*str))
		{
			game_v->res_w = ft_substr(str, 0, ft_numlen(&str));
			game_v->res_w_nu = ft_atoi(game_v->res_w);
		}
		else
			return ;
		ft_jump_spaces(&str);
		if (ft_isdigit(*str))
		{
			game_v->res_h = ft_substr(str, 0, ft_numlen(&str));
			game_v->res_h_nu = ft_atoi(game_v->res_h);
		}
		else
			return ;
	}
}

static void	line_colors_analizer(char *str, t_game_v *game_v)
{
	ft_jump_spaces(&str);
	if (*str == 'C')
		fill_color(&str, 1, game_v->ceiling_color);
	else if (*str == 'F')
		fill_color(&str, 1, game_v->floor_color);
}

static void	analizers(char *line, t_game_v *game_v)
{
	line_texture_analizer(line, game_v);
	line_measures_analizer(line, game_v);
	line_colors_analizer(line, game_v);
}

int			game_v_filler(t_game_v *game_v, char *file_path)
{
	int		game_v_fd;
	char	*line;

	line = 0;
	game_v_fd = open(file_path, 00);
	while (get_next_line(game_v_fd, &line))
	{
		analizers(line, game_v);
		free(line);
		if (is_map_moment(game_v))
			break ;
	}
	while (get_next_line(game_v_fd, &line))
	{
		add_string_to_mat(&game_v->map, line);
		free(line);
	}
	add_string_to_mat(&game_v->map, line);
	free(line);
	if (are_game_v_ok(game_v))
		return (1);
	free_game_v(game_v);
	printf("\nError\n");
	return (0);
}
