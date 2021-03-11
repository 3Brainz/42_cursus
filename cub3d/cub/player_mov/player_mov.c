#include "../libcub.h"

void	decrement_degree(float *inclination, float degree)
{
	if (*inclination + degree >= 2 * M_PI)
		*inclination = -2 * M_PI;
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
		next_y = P_POSY + (player->speed * cos(P_INCL));
		next_x = P_POSX + (player->speed * sin(P_INCL));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			P_POSY = next_y;
			P_POSX = next_x;
		}
	}
	else if (dir == 'F')
	{
		next_y = P_POSY - (player->speed * cos(P_INCL));
		next_x = P_POSX - (player->speed * sin(P_INCL));
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

	if (dir == 'L')
	{
		next_y = P_POSY + (player->speed * cos(P_INCL + M_PI / 2));
		next_x = P_POSX + (player->speed * sin(P_INCL + M_PI / 2));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			P_POSY = next_y;
			P_POSX = next_x;
		}
	}
	else if (dir == 'R')
	{
		next_y = P_POSY - (player->speed *
									cos(P_INCL + M_PI / 2));
		next_x = P_POSX - (player->speed *
									sin(P_INCL + M_PI / 2));
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
	if (keys->left_arrow)
		decrement_degree(&P_INCL, ONE_DEGREE);
	if (keys->right_arrow)
		increment_degree(&P_INCL, ONE_DEGREE);
	if (keys->w_key)
		straight_mov(player, 'F', map);
	if (keys->a_key)
		side_mov(player, 'R', map);
	if (keys->s_key)
		straight_mov(player, 'B', map);
	if (keys->d_key)
		side_mov(player, 'L', map);
}
