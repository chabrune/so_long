/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:07 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/20 19:02:25 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**map_read(int fd, t_map *map, t_data *data)
{
	t_list	*list;
	char	*line;
	t_list	*tmp;
	int		i;

	i = 0;
	list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_lstnew(line);
		ft_lstadd_back(&list, tmp);
		line = get_next_line(fd);
	}
	map->maps = calloc(sizeof(char *), ft_lstsize(list) + 1);
	if (!map->maps)
		return (NULL);
	map->y = ft_lstsize(list);
	tmp = list;
	while (tmp)
	{
		map->maps[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	free(tmp);
	free(list);
	free(line);
	map->x = ft_strlen_sl(*map->maps);
	data->map.maps = map->maps;
	return (map->maps);
}

void	ft_check_error(int ac, t_map map, char *s, t_data *data)
{
	if (ac != 2)
		print_error("Nombre d'arguments", data);
	if (check_error_name(s) == -1)
		print_error("Nom de la map invalide", data);
	if (check_rectangular(map.maps, map) == -1)
		print_error("Map invalide rectangle", data);
	if (check_full_one(map) == -1)
		print_error("Map invalide 1", data);
	check_p_position(data);
	if (check_letter(data) == -1)
		print_error("Letter invalide", data);
}

void	print_error(char *msg, t_data *data)
{
	ft_printf("Error\n");
	ft_putstr(msg);
	free(data);
	exit(0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	map;
	t_data	*data;

	data = malloc(sizeof(t_data));
	fd = open(argv[1], O_RDWR);
	if (fd == -1 || !read(fd, "1", 1))
		return (ft_printf("Error\nFichier vide"));
	map.maps = map_read(fd, &map, data);
	set_data(data, map);
	ft_check_error(argc, map, argv[1], data);
	if (flood_fill(*data, &map, argv[1]) == -1)
		print_error("Map invalide", data);
	open_window(data);
	close(fd);
	free(data);
	free(&map);
	return (0);
}
