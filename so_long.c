/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:07 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/11 03:17:31 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char **map_read(int fd, t_map *map)
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
		tmp = ft_lstnew(line);
		ft_lstadd_back(&list, tmp);
		line = get_next_line(fd);
	}
	maps = calloc(sizeof(char *), ft_lstsize(list) + 1);
	if (!maps)
		return (NULL);
	map->y = ft_lstsize(list);
	tmp = list;
	while (tmp)
	{
		maps[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	map->x = ft_strlen(*maps);
	return maps;
}

int	ft_check_error(int ac, t_map map, char *s, t_data *data)
{
	if(ac != 2)
		return(ft_printf("Error\nNombre d'argument invalide"));
	if (check_error_name(s) == - 1)
		return(ft_printf("Error\nNom de la map invalide"));
	if (check_rectangular(map.maps) == - 1)
		return(ft_printf("Error\nMap invalide rectangle"));
	if (check_full_one(map) == - 1)
		return(ft_printf("Error\nMap invalide 1"));
	if (check_letter(data) == - 1)
		return(ft_printf("Error\nLetter invalide"));
	if (flood_fill(*data, &map, s) == - 1)
		return(ft_printf("Error\nMap invalide"));
}



int main(int argc, char **argv)
{
	int fd;
	t_map map;
	t_data data;

	fd = open(argv[1], O_RDWR);
	if (fd == - 1 || !read(fd, "1", 1))
		return(ft_printf("Error\nFichier vide"));
	map.maps = map_read(fd, &map);
	set_data(&data, map);
	ft_check_error(argc, map, argv[1], &data);
	open_window(&data);
	return (0);
}