/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:47:43 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/13 16:47:45 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void	decrement_degree(float *inclination, float degree)
{
	if (*inclination + degree >= 2 * M_PI)
		*inclination = 0;
	else
		*inclination += degree;
}

void	increment_degree(float *inclination, float degree)
{
	if (*inclination - degree < 0)
	{
		*inclination = (2 * M_PI) - ONE_DEGREE;
	}
	else
		*inclination -= degree;
}

void	straight_mov(t_player *player, char dir, char **map)
{
	float next_y;
	float next_x;

	if (dir == 'B')
	{
		next_y = P_POSY + (player->speed * sin(P_INCL));
		next_x = P_POSX + (player->speed * cos(P_INCL));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			P_POSY = next_y;
			P_POSX = next_x;
		}
	}
	else if (dir == 'F')
	{
		next_y = P_POSY - (player->speed * sin(P_INCL));
		next_x = P_POSX - (player->speed * cos(P_INCL));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			P_POSY = next_y;
			P_POSX = next_x;
		}
	}
}

void	side_mov(t_player *player, int dir, char **map)
{
	float next_y;
	float next_x;

	if (dir == 'R')
	{
		next_y = P_POSY + (player->speed * sin(P_INCL + M_PI / 2));
		next_x = P_POSX + (player->speed * cos(P_INCL + M_PI / 2));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			P_POSY = next_y;
			P_POSX = next_x;
		}
	}
	else if (dir == 'L')
	{
		next_y = P_POSY - (player->speed *
									sin(P_INCL + M_PI / 2));
		next_x = P_POSX - (player->speed *
									cos(P_INCL + M_PI / 2));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			P_POSY = next_y;
			P_POSX = next_x;
		}
	}
}

void	player_movement(t_keys *keys, t_player *player, char **map)
{
	if (keys->shift)
		player->speed = RUNNING_SPEED;
	else if(!keys->shift)
		player->speed = NORMAL_SPEED;
	if (keys->right_arrow)
	{
		double oldDirX =player->plane->dir_x;
		player->plane->dir_x = player->plane->dir_x * cos(ONE_DEGREE) - player->plane->dir_y * sin(ONE_DEGREE);
		player->plane->dir_y = oldDirX * sin(ONE_DEGREE) + player->plane->dir_y * cos(ONE_DEGREE);
		double oldPlaneX = player->plane->plane_x;
		player->plane->plane_x = player->plane->plane_x * cos(ONE_DEGREE) - player->plane->plane_y * sin(ONE_DEGREE);
		player->plane->plane_y= oldPlaneX * sin(ONE_DEGREE) + player->plane->plane_y * cos(ONE_DEGREE);
		decrement_degree(&P_INCL, ONE_DEGREE);
	}
	if (keys->left_arrow)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->plane->dir_x;
		player->plane->dir_x = player->plane->dir_x * cos(-ONE_DEGREE) - player->plane->dir_y * sin(-ONE_DEGREE);
		player->plane->dir_y = oldDirX * sin(-ONE_DEGREE) + player->plane->dir_y * cos(-ONE_DEGREE);
		double oldPlaneX = player->plane->plane_x;
		player->plane->plane_x = player->plane->plane_x * cos(-ONE_DEGREE) - player->plane->plane_y * sin(-ONE_DEGREE);
		player->plane->plane_y = oldPlaneX * sin(-ONE_DEGREE) + player->plane->plane_y * cos(-ONE_DEGREE);
		increment_degree(&P_INCL, ONE_DEGREE);
	}
	if (keys->w_key)
		straight_mov(player, 'F', map);
	if (keys->a_key)
		side_mov(player, 'R', map);
	if (keys->s_key)
		straight_mov(player, 'B', map);
	if (keys->d_key)
		side_mov(player, 'L', map);
}
