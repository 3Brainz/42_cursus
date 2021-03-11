#include "../libcub.h"

void	player_movement(t_keys *keys, t_player *player, char **map)
{
	char c = **map;
	c = 0;
	if (keys->left_arrow)
		player->inclination -= ONE_DEGREE;
	if (keys->right_arrow)
		player->inclination += ONE_DEGREE;
}