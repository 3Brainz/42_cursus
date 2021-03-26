/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:58:12 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/25 16:58:14 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

int		mouse_click(int button, int pos_x, int pos_y, t_window *window)
{
	window->click->button = button;
	window->click->pos_x = pos_x;
	window->click->pos_y = pos_y;
	clean_mouse_click(window->click);
	return (0);
}

int		mouse_pos_mov(int x, int y, t_window *window)
{
	window->mouse_pos->pos_x = x;
	window->mouse_pos->pos_y = y;
	return (0);
}
