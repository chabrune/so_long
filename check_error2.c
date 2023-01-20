/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:10:22 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/20 18:55:00 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	flood_fill(t_data data, t_map *map, char *path)
{
	int		fd;
	int		collect;
	char	**mapff;

	fd = open(path, O_RDWR);
	mapff = map_read(fd, map, &data);
	collect = f_fill(mapff, data.P_position.x, \
		data.P_position.y);
	if (collect != data.check_C)
		return (-1);
	close(fd);
	free(mapff);
	return (0);
}

int	f_fill(char **mapff, int x, int y)
{
	static int	i = 0;

	if (x < 0 || y < 0 || mapff[x][y] == '1')
		return (0);
	if (mapff[x][y] == 'C')
		i++;
	mapff[x][y] = '1';
	f_fill(mapff, x - 1, y);
	f_fill(mapff, x + 1, y);
	f_fill(mapff, x, y - 1);
	f_fill(mapff, x, y + 1);
	return (i);
}
