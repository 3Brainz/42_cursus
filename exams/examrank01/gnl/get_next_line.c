/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:06:45 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/02 13:06:47 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
	int index;
	
	index = 0;
	while (str[index])
	{
		index++;
	}
	return (index);
}
/*
int get_next_line(int fd, char **line)
{
	size_t	buff_index = 0;
	int red;
	char buffer[1024*1024];
	
	if (!line)
		return (-1);
	while ((red = read(fd, &buffer[buff_index], 1)) >= 0)
	{
		if (buffer[buff_index] == '\n' || red == 0)
		{
			buffer[buff_index] = 0;
			*line = (char *)malloc(sizeof(char) * (ft_strlen(buffer) + 1));
			if (!*line)
				return (-1);
			buff_index = 0;
			while (buffer[buff_index])
			{
				(*line)[buff_index] = buffer[buff_index];
				buffer[buff_index] = 0;
				buff_index++;
			}
			(*line)[buff_index] = 0;
			return(red == 0 ? 0 : 1);
		}
		else
			buff_index++;
	}
	return (-1);
}
*/
int get_next_line(char **line)
{
	char	buffer[1024*1024];
	int		red;
	size_t	buff_index;
	
	if (!line)
		return (-1);
	while ((red = read(0, &buffer[buff_index], 1)) >= 0)
	{
		if (buffer[buff_index] == '\n' || red == 0)
		{
			buffer[buff_index] = 0;
			*line = (char *)malloc(sizeof(char) * (ft_strlen(buffer) + 1));
			if (!*line)
				return (-1);
			buff_index = 0;
			while (buffer[buff_index])
			{
				line[0][buff_index] = buffer[buff_index];
				buffer[buff_index] = 0;
				buff_index++;
			}
			line[0][buff_index] = 0;
			if (red == 0)
				return (0);
			else
				return (1);
		}
		else
			buff_index++;
	}
	return (-1);
}
