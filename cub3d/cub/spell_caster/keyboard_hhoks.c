#include "../libcub.h"

void		set_key_on(int *key, int to)
{
	*key = to;
}

int			key_hook_in(int keycode, t_window *window)
{
	printf("keycode_in:%i,windowptr:%p\n", keycode, window);
	return (0);
}

int 		key_hook_out(int keycode, t_window *window)
{
	printf("keycode_out:%i,windowptr:%p\n", keycode, window);
	return (0);
}

