/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:32:07 by ppunzo            #+#    #+#             */
/*   Updated: 2021/02/27 11:32:09 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub/libcub.h"
#include <mlx.h>

int main(int argc, char **argv)
{
	
	t_game_v game_v;
	int a = 1;

	void *mlx = mlx_init ();
	if (argc == 2)
		printf("%s", argv[1]);
	game_v_cleaner(&game_v);
	game_v_filler(&game_v, "./map.cub");

	mlx_new_window(mlx, 200, 200, "wewe");
	while (a == 1)
		a = 1;
	return (0);
}
