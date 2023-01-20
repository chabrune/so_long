/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:56:34 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/20 17:47:42 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_error_name(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if ((s[i - 1] != 'r' && s[i - 2] != 'e' && s[i - 3] != 'b'
			&& s[i - 4] != '.') || ft_strlen_sl(s) < 4)
		return (-1);
	return (0);
}

int	check_rectangular(char **maps, t_map map)
{
	int	i;

	i = 0;
	while (i < map.y)
	{
		if (ft_strlen_sl(maps[i]) != map.x)
			return (-1);
		i++;
	}
	return (0);
}

int	check_letter(t_data *data)
{
	data->map.x = 0;
	while (data->map.maps[data->map.x])
	{
		data->map.y = 0;
		while (data->map.maps[data->map.x][data->map.y])
		{
			if (data->map.maps[data->map.x][data->map.y] == 'C')
				data->check_C++;
			if (data->map.maps[data->map.x][data->map.y] == 'E')
				data->check_E++;
			if (data->map.maps[data->map.x][data->map.y] != 'P'
				&& data->map.maps[data->map.x][data->map.y] != 'C'
				&& data->map.maps[data->map.x][data->map.y] != 'E'
				&& data->map.maps[data->map.x][data->map.y] != '0'
				&& data->map.maps[data->map.x][data->map.y] != '1')
				return (-1);
			data->map.y++;
		}
		data->map.x++;
	}
	if (data->check_C < 1 || data->check_E != 1)
		return (-1);
	return (0);
}

int	check_p_position(t_data *data)
{
	data->map.x = 0;
	while (data->map.maps[data->map.x])
	{
		data->map.y = 0;
		while (data->map.maps[data->map.x][data->map.y])
		{
			if (data->map.maps[data->map.x][data->map.y] == 'P')
			{
				data->P_position.x = data->map.x;
				data->P_position.y = data->map.y;
				data->check_P++;
			}
			data->map.y++;
		}
		data->map.x++;
	}
	if (data->check_P != 1)
		return (-1);
	return (0);
}

int	check_full_one(t_map map)
{
	map.x = 0;
	while (map.maps[map.x])
	{
		map.y = 0;
		if (map.maps[map.x][map.y] != '1')
			return (-1);
		while (map.maps[map.x][map.y])
		{
			if (map.maps[0][map.y] != '1')
				return (-1);
			map.y++;
		}
		if (map.maps[map.x][map.y - 1] != '1')
			return (-1);
		map.x++;
	}
	map.y = 0;
	while (map.maps[map.x - 1][map.y])
	{
		if (map.maps[map.x - 1][map.y] != '1')
			return (-1);
		map.y++;
	}
	return (0);
}
