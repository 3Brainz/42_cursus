#include "../libcub.h"

int		key_hook(int keycode, t_window *window)
{
	printf("keycode:%i\nwindowptr:%p\n", keycode, window);
	
	return (0);
}
