
#include "../libcub.h"

int				just_one_player(char **map)
{
	int		y_index;
	int		x_index;
	char	pos;
	char	c;

	pos = 0;
	y_index = 0;
	x_index = 0;
	while (map[y_index])
	{
		x_index = 0;
		while ((c = map[y_index][x_index]))
		{
			if (is_in_cset(c, "NOWS"))
			{
				if(!pos)
					pos = c;
				else
					return (0);
			}
			x_index++;
		}
		y_index++;
	}
	if (!pos)
		return (0);
	return (1);
}

static void		plane_positioner(t_player *player, char dir)
{
	plane_cleaner(player->plane);
	if (dir == 'N')
	{
		player->plane->rel_dir_y = -1;
		player->plane->plane_v_x = -0.66;
	}
	if (dir == 'E')
	{
		player->plane->rel_dir_x = 1;
		player->plane->plane_v_y = 0.66;
	}
	if (dir == 'S')
	{
		player->plane->rel_dir_y = 1;
		player->plane->plane_v_x = 0.66;
	}
	if (dir == 'O')
	{
		player->plane->rel_dir_x = -1;
		player->plane->plane_v_y = -0.66;
	}
}

static void		player_directioner(t_player *player, char dir)
{
	if (dir == 'N')
		player->inclination = 0;
	if (dir == 'E')
		player->inclination = M_PI / 2;
	if (dir == 'S')
		player->inclination = M_PI;
	if (dir == 'O')
		player->inclination = 3 * M_PI / 2;
}

void			player_positioner(t_player *player, int pos_x, int pos_y, char dir)
{
	player->pos_x = pos_x + 0.5;
	player->pos_y = pos_y + 0.5;
	player_directioner(player, dir);
	plane_positioner(player, dir);
}

void 			where_is_the_player(char **map, t_player *player)
{
	int		x_index;
	int		y_index;
	char	c;

	x_index = 0;
	y_index = 0;
	while (map[y_index])
	{
		x_index = 0;
		while ((c = map[y_index][x_index]))
		{
			if (is_in_cset(c, "NOSW"))
			{
				player_positioner(player, x_index, y_index, c);
				map[y_index][x_index] = 0;
				return ;
			}
			x_index++;
		}
		y_index++;
	}
}