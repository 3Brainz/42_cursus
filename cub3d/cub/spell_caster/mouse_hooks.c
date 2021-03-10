#include "../libcub.h"

void	mouse_click_print(t_mouse_ck *click)
{
	printf("button:%i\n", click->button);
	printf("pos_x:%i\n", click->pos_x);
	printf("pos_uy:%i\n", click->pos_y);
}

int		mouse_click(int button, int pos_x,int pos_y, t_window *window)
{
	window->click->button = button;
	window->click->pos_x = pos_x;
	window->click->pos_y = pos_y;
	mouse_click_print(window->click);
	clean_mouse_click(window->click);
	return (0);
}

int		mouse_pos_mov(int x, int y, t_window *window)
{
	window->mouse_pos->pos_x = x;
	window->mouse_pos->pos_y = y;
	//printf("pos_x:%i,pos_y:%i\n", window->mouse_pos->pos_x, window->mouse_pos->pos_y);
	return (0);
}