/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:07 by chabrune          #+#    #+#             */
/*   Updated: 2022/12/19 15:07:49 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		// ft_printf("%s", line);
		tmp = ft_lstnew(line);
		ft_lstadd_back(&list, tmp);
		line = get_next_line(fd);
	}
	// ft_printf("\n");
	maps = malloc(sizeof(char *) * ft_lstsize(list));
	if (!maps)
		return (NULL);
	while (list)
	{
		maps[i] = ft_strdup(list->content);
		ft_lstdelone(list, free);
		// ft_printf("%s\n", maps[i]);
		list = list->next;
		i++;
	}
	return maps;
}

int	check_error(char **maps)
{
	int i;

	i = 0;
	while(maps[i])
	{
		if(ft_strlen(maps[i]) != ft_strlen(maps[i + 1]))
		{
			ft_printf("Error\nMap invalide");
			return (-1);
		}
		i++;
	}
	i = 0;
	if (maps[i][0] != 1 && maps[i][strlen(*maps)] != 1)
	return (0);
}

int main(int argc, char **argv)
{
	int fd;
	char **maps;
	int i;

	i = 0;
	while(argv[1][i])
		i++;
	if((argv[1][i - 1] != 'r' && argv[1][i - 2] != 'e' && argv[1][i - 3] != 'b' && argv[1][i - 4] != '.') || ft_strlen(argv[1]) < 4)
	{
		ft_printf("Error\nNom de la map invalide");
		return(-1);
	}
	if (argc != 2)
	{
		ft_printf("Error\nNombre d'argument invalide");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	maps = map_read(fd);
	if (check_error(maps) == -1)
		return (-1);
}
