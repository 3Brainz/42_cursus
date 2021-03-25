#ifndef LIBCUB_BONUS_H
# define LIBCUB_BONUS_H
# include "libcub.h"

/*
**Minimap
*/

void			minimap_img(t_data *img, t_window *window, t_player *player,
							int min_fract);
void			mouse_rot(t_window *window);
#endif