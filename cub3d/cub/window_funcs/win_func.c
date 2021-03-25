/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:40:32 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/05 15:40:42 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void		start_win(t_window *window, t_game_v *game_v)
{
	int res_w;
	int res_h;

	res_w = ft_atoi(game_v->res_w);
	res_h = ft_atoi(game_v->res_h);
	window->game_v = game_v;
	where_is_the_player(window->game_v->map, window->player);
	clean_keys(window->keys);
	window->mlx = mlx_init();
	window->mlx_win = mlx_new_window(window->mlx, res_w, res_h, "ROOM");
}

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		new_image(t_data *image, t_window *window, int width, int height)
{
	image->img = mlx_new_image(window->mlx, width, height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
									&image->line_length, &image->endian);
}

static void	free_win(t_window *window)
{
	free(window->textuures->e_texture->addr);
	free(window->textuures->n_texture->addr);
	free(window->textuures->s_textture->addr);
	free(window->textuures->w_texture->addr);
	free(window->textuures->sprite_texture->addr);
	if (window->game_v->bonus)
		free(window->textuures->skybox->addr);
}

int			close_game(t_window *window)
{
	mlx_destroy_window(window->mlx, window->mlx_win);
	free_game_v(window->game_v);
	free_win(window);
	exit(0);
	return (0);
}
