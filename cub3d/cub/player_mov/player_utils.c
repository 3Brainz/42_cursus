/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:47:29 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/13 16:47:30 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void	plane_cleaner(t_plane *plane)
{
	plane->dir_x = 0;
	plane->dir_y = 0;
	plane->plane_x = 0;
	plane->plane_y = 0;
}