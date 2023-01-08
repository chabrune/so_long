/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:07 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/08 14:57:35 by chabrune         ###   ########.fr       */
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
		tmp = ft_lstnew(line);
		ft_lstadd_back(&list, tmp);
		line = get_next_line(fd);
	}
	maps = malloc(sizeof(char *) * ft_lstsize(list));
	if (!maps)
		return (NULL);
	while (list)
	{
		maps[i] = ft_strdup(list->content);
		ft_lstdelone(list, free);
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
				data->P_position.x = data->map.x;
				data->P_position.y = data->map.y;
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

void	ft_init(t_data *data, t_map map)
{
	data->mlx = mlx_init((map.y * 64), (map.x * 64), "so_long", false);
	data->perso = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/perso.png"));
	data->wall = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/wall.png"));
	data->col = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/collect.png"));
	data->land = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/land.png"));
	data->exit = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/wall.png"));
}

void	image_to_window(t_data *data, t_map map)
{
	map.x = 0;
	while (map.maps[map.x])
	{
		map.y = 0;
		while(map.maps[map.x][map.y])
		{
			mlx_image_to_window(data->mlx, data->land, (64 * map.y), (64 * map.x));
			if (map.maps[map.x][map.y] == 'C')
				mlx_image_to_window(data->mlx, data->col, (64 * map.y), (64 * map.x));
			if (map.maps[map.x][map.y] == 'E')
				mlx_image_to_window(data->mlx, data->exit, (64 * map.y), (64 * map.x));
			if (map.maps[map.x][map.y] == '1')
				mlx_image_to_window(data->mlx, data->wall, (64 * map.y), (64 * map.x));
			map.y++;
		}
		map.x++;
	}
}

void	hook(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = param;
	(void)keydata;
	// data->perso->instances[0].enabled = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if(data->map.maps[(data->perso->instances[0].y /64) - 1][data->perso->instances[0].x / 64] != '1')
			data->perso->instances[0].y -= 64;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		 data->perso->instances[0].y += 64;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		 data->perso->instances[0].x -= 64;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		 data->perso->instances[0].x += 64;
}

int	open_window(t_data *data)
{
	ft_init(data, data->map);
	image_to_window(data, data->map);
	mlx_image_to_window(data->mlx, data->perso, (64 * data->P_position.y), (64 * data->P_position.x));
	mlx_key_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}


int main(int argc, char **argv)
{
	int fd;
	int i;
	t_map map;
	t_data data;

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
	open_window(&data);
	return (0);
}
