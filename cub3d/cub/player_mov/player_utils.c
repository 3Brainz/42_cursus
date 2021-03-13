#include "../libcub.h"

void plane_cleaner(t_plane *plane)
{
	plane->rel_dir_x = 0;
	plane->rel_dir_y = 0;
	plane->plane_v_x = 0;
	plane->plane_v_y = 0;
}