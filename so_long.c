/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:07 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/07 18:54:11 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_data(t_data *data, t_map map)
{
	data->map.maps = map.maps;
	data->map.x = 0;
	data->map.y = 0;
	data->check_C = 0;
	data->check_E = 0;
	data->check_P = 0;
    data->foot_count = 0;
    data->C_count = 0;
}

char **map_read(int fd)
{
	t_list *list;
	char *line;
	t_list *tmp;
	char **maps;
	int i;

	i = 0;
	list = NULL;
	line = get_next_line(fd);
	while(line)
	{
		ft_printf("%s", line);
		tmp = ft_lstnew(line);
		ft_lstadd_back(&list, tmp);
		line = get_next_line(fd);
	}
	ft_printf("\n");
	maps = malloc(sizeof(char *) * ft_lstsize(list));
	if (!maps)
		return (NULL);
	while (list)
	{
		maps[i] = ft_strdup(list->content);
		ft_lstdelone(list, free);
		ft_printf("%s\n", maps[i]);
		list = list->next;
		i++;
	}
	maps[i] = NULL;
	return maps;
}

int ckeck_full_one(t_map map)
{
	map.x = 0;
	while(map.maps[map.x])
	{
		map.y = 0;
		if (map.maps[map.x][map.y] != '1')
			return(-1);
		while (map.maps[map.x][map.y])
		{
			if(map.maps[0][map.y] != '1')
				return(-1);
			map.y++;
		}
		if(map.maps[map.x][map.y - 1] != '1')
			return (-1);
		map.x++;
	}
	map.y = 0;
	while(map.maps[map.x - 1][map.y])
	{
		if (map.maps[map.x - 1][map.y] != '1')
				return(-1);
		map.y++;
	}
	return(0);
}

int check_letter(t_data *data)
{
	// data->check_C = 0;
	// check_E = 0;
	// check_P = 0;
	while(data->map.maps[data->map.x])
	{
		data->map.y = 0;
		while (data->map.maps[data->map.x][data->map.y])
		{
			if(data->map.maps[data->map.x][data->map.y] == 'C')
				data->check_C++;
			if(data->map.maps[data->map.x][data->map.y] == 'E')
				data->check_E++;
			if(data->map.maps[data->map.x][data->map.y] == 'P')
			{
				data->check_P++;
			}
			if(data->map.maps[data->map.x][data->map.y] != 'P' 
				&& data->map.maps[data->map.x][data->map.y] != 'C'
				&& data->map.maps[data->map.x][data->map.y] != 'E' 
				&& data->map.maps[data->map.x][data->map.y] != '0'
				&& data->map.maps[data->map.x][data->map.y] != '1')
				return(-1);
			data->map.y++;
		}
		data->map.x++;
		ft_printf("%d\n", data->map.y);
	}
	if(data->check_C < 1 || data->check_E != 1 || data->check_P != 1)
		return(-1);
	return(0);
}

int	check_error(char **maps)
{
	int i;

	i = 1;
	while (maps[i])
	{
		if (i >= 1 && ft_strlen(maps[i]) != ft_strlen(maps[i - 1]))
		{
			ft_printf("Error\nMap invalide rectangle");
			return (-1);
		}
		i++;
	}
	return (0);
}

int check_error_name(char *s)
{
	int	i;

	i = 0;
	while(s[i])
		i++;
	if((s[i - 1] != 'r' && s[i - 2] != 'e' && s[i - 3] != 'b' && s[i - 4] != '.') 
		|| ft_strlen(s) < 4)
	{
		ft_printf("Error\nNom de la map invalide");
		return(-1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	int fd;
	int i;
	t_map map;
	t_data data;

	//data = NULL;
	i = 0;
	if (argc != 2)
	{
		ft_printf("Error\nNombre d'argument invalide");
		return (-1);
	}
	if (check_error_name(argv[1]) == -1)
		return(-1);
	fd = open(argv[1], O_RDWR);
	if (fd == - 1 || !read(fd, "1", 1))
	{
		ft_printf("Error\nFichier vide");
		return(-1);
	}
	map.maps = map_read(fd);
	set_data(&data, map);
	if (check_error(map.maps) == -1)
		return (-1);
	if (ckeck_full_one(map) == -1)
	{
		ft_printf("Error\nMap invalide 1");
		return (-1);
	}
	if (check_letter(&data) == -1)
	{
		ft_printf("Error\nLetter invalide");
		return(-1);
	}
	return (0);
}
