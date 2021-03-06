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

void	start_win(t_window *window, t_game_v *game_v)
{
	int res_w;
	int res_h;

	res_w = ft_atoi(game_v->res_w);
	res_h = ft_atoi(game_v->res_h);
	window->mlx = mlx_init ();
	window->mlx_win = mlx_new_window(window->mlx, res_w, res_h, "wewe");
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	new_image(t_data *image, t_window *window, int width, int height)
{
	image->img = mlx_new_image(window->mlx, width, height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
}