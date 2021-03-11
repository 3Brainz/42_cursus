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
		next_y = player->pos_y + (player->speed * cos(player->inclination));
		next_x = player->pos_x + (player->speed * sin(player->inclination));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			player->pos_y = next_y;
			player->pos_x = next_x;
		}
	}
	else if (dir == 'F')
	{
		next_y = player->pos_y - (player->speed * cos(player->inclination));
		next_x = player->pos_x - (player->speed * sin(player->inclination));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			player->pos_y = next_y;
			player->pos_x = next_x;
		}
	}
}

void	side_mov(t_player *player, int dir, char **map)
{
	float next_y;
	float next_x;
	if (dir == 'L')
	{
		next_y = player->pos_y + (player->speed * cos(player->inclination + M_PI / 2));
		next_x = player->pos_x + (player->speed * sin(player->inclination + M_PI / 2));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			player->pos_y = next_y;
			player->pos_x = next_x;
		}
	}
	else if (dir == 'R')
	{
		next_y = player->pos_y - (player->speed * cos(player->inclination + M_PI / 2));
		next_x = player->pos_x - (player->speed * sin(player->inclination + M_PI / 2));
		if (map[(int)next_y][(int)next_x] == '0')
		{
			player->pos_y = next_y;
			player->pos_x = next_x;
		}
	}
}

void	player_movement(t_keys *keys, t_player *player, char **map)
{
	char c = **map;
	c = 0;
	if (keys->shift)
		player->speed = RUNNING_SPEED;
	else if(!keys->shift)
		player->speed = NORMAL_SPEED;
	if (keys->left_arrow)
		decrement_degree(&player->inclination, ONE_DEGREE);
	if (keys->right_arrow)
		increment_degree(&player->inclination, ONE_DEGREE);
	if (keys->w_key)
		straight_mov(player, 'F', map);
	if (keys->a_key)
		side_mov(player, 'R', map);
	if (keys->s_key)
		straight_mov(player, 'B', map);
	if (keys->d_key)
		side_mov(player, 'L', map);
}