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

void		decrement_degree(float *inclination, float degree, t_plane *plane)
{
	double oldDirX;
	double oldPlaneX;

	if (*inclination + degree >= 2 * M_PI)
		*inclination = 0;
	else
		*inclination += degree;
	oldDirX = plane->dir_x;
	plane->dir_x = plane->dir_x * cos(ONE_DEGREE) - plane->dir_y * sin(ONE_DEGREE);
	plane->dir_y = oldDirX * sin(ONE_DEGREE) + plane->dir_y * cos(ONE_DEGREE);
	oldPlaneX = plane->plane_x;
	plane->plane_x = plane->plane_x * cos(ONE_DEGREE) - plane->plane_y * sin(ONE_DEGREE);
	plane->plane_y= oldPlaneX * sin(ONE_DEGREE) + plane->plane_y * cos(ONE_DEGREE);
}

void		increment_degree(float *inclination, float degree, t_plane *plane)
{
	double oldDirX;
	double oldPlaneX;
	
	if (*inclination - degree < 0)
	{
		*inclination = (2 * M_PI) - ONE_DEGREE;
	}
	else
		*inclination -= degree;
	oldDirX = plane->dir_x;
	plane->dir_x = plane->dir_x * cos(-ONE_DEGREE) - plane->dir_y * sin(-ONE_DEGREE);
	plane->dir_y = oldDirX * sin(-ONE_DEGREE) + plane->dir_y * cos(-ONE_DEGREE);
	oldPlaneX = plane->plane_x;
	plane->plane_x = plane->plane_x * cos(-ONE_DEGREE) - plane->plane_y * sin(-ONE_DEGREE);
	plane->plane_y = oldPlaneX * sin(-ONE_DEGREE) + plane->plane_y * cos(-ONE_DEGREE);
}

static void	straight_mov(t_player *player, char dir, char **map)
{
	t_plane *plane;

	plane = player->plane;
	if (dir == 'B')
	{
		if(map[(int)(player->pos_y)]
				[(int)(player->pos_x + plane->dir_x * player->speed)] == '0')
			player->pos_x += plane->dir_x * player->speed;
    	if(map[(int)(player->pos_y + plane->dir_y * player->speed)]
				[(int)(player->pos_x)] == '0')
			player->pos_y += plane->dir_y * player->speed;
	}
	else if (dir == 'F')
	{
		if(map[(int)(player->pos_y)]
				[(int)(player->pos_x - plane->dir_x * player->speed)] == '0')
			player->pos_x -= plane->dir_x * player->speed;
    	if(map[(int)(player->pos_y - plane->dir_y * player->speed)]
				[(int)(player->pos_x)] == '0')
			player->pos_y -= plane->dir_y * player->speed;
	}
}

static void	side_mov(t_player *player, int dir, char **map)
{
	if (dir == 'R')
	{
		if (map[(int)player->pos_y][(int)(player->pos_x - player->plane->plane_x
		* 5 * player->speed)] == '0')
			player->pos_x -= (player->plane->plane_x * player->speed);
		if (map[(int)(player->pos_y - player->plane->plane_y
		* 5 * player->speed )][(int)player->pos_x] == '0')
			player->pos_y -= (player->plane->plane_y * player->speed);
	}
	else if (dir == 'L')
	{
		if (map[(int)player->pos_y][(int)(player->pos_x + player->plane->plane_x
		* 5 * player->speed)] == '0')
			player->pos_x += (player->plane->plane_x * player->speed);
		if (map[(int)(player->pos_y + player->plane->plane_y
		* 5 * player->speed )][(int)player->pos_x] == '0')
			player->pos_y += (player->plane->plane_y * player->speed);
	}
}

void	player_movement(t_keys *keys, t_player *player, char **map)
{
	if (keys->shift)
		player->speed = RUNNING_SPEED;
	else if(!keys->shift)
		player->speed = NORMAL_SPEED;
	if (keys->right_arrow)
		decrement_degree(&P_INCL, ONE_DEGREE, player->plane);
	if (keys->left_arrow)
		increment_degree(&P_INCL, ONE_DEGREE, player->plane);
	if (keys->w_key)
		straight_mov(player, 'B', map);
	if (keys->a_key)
		side_mov(player, 'L', map);
	if (keys->s_key)
		straight_mov(player, 'F', map);
	if (keys->d_key)
		side_mov(player, 'R', map);
}
