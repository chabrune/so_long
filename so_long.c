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
	data->map.x = 0;
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
			if(data->map.maps[data->map.x][data->map.y] != 'P' && data->map.maps[data->map.x][data->map.y] != 'C' && data->map.maps[data->map.x][data->map.y] != 'E' && data->map.maps[data->map.x][data->map.y] != '0' && data->map.maps[data->map.x][data->map.y] != '1')
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
	ft_printf("%d\n%d\n", data->map.y, data->map.x);
	data->mlx = mlx_init((map.y * 64), (map.x * 64), "so_long", false);
	data->perso = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/perso.png"));
	data->wall = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/wall.png"));
	data->col = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/collect.png"));
	data->land = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/land.png"));
	data->exit = mlx_texture_to_image(data->mlx, mlx_load_png("PNG/exit.png"));
}

void	image_to_window(t_data *data, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->x)
	{
		j = 0;
		while(j < map->y)
		{
			mlx_image_to_window(data->mlx, data->land, (64 * j), (64 * i));
			if (map->maps[i][j] == 'C')
				mlx_image_to_window(data->mlx, data->col, (64 * j), (64 * i));
			if (map->maps[i][j] == 'E')
				mlx_image_to_window(data->mlx, data->exit, (64 * j), (64 * i));
			if (map->maps[i][j] == '1')
				mlx_image_to_window(data->mlx, data->wall, (64 * j), (64 * i));
			j++;
		}
		i++;
	}
}

void	collect_to_window(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while(j < 34)
		{
			if (data->map.maps[i][j] == 'E')
				mlx_image_to_window(data->mlx, data->exit, (64 * j), (64 * i));
			j++;
		}
		i++;
	}
}

int f_fill(char **mapff, int x, int y)
{
	static int i = 0;
    if (mapff[x][y] == '1')
        return 0;
	if (mapff[x][y] == 'C' || mapff[x][y] == 'E')
		i++;
    mapff[x][y] = '1';

    f_fill(mapff, x -1, y);
    f_fill(mapff, x +1, y);
    f_fill(mapff, x, y - 1);
    f_fill(mapff, x, y + 1);
	return(i);
}

int  flood_fill(t_data data, t_map *map, char *path)
{
	int fd;
	int collect;
	char **mapff;

	fd = open(path, O_RDWR);
	mapff = map_read(fd, map); 
	collect = f_fill(mapff, data.P_position.x, data.P_position.y);
	data.check_C++;
	if (collect != data.check_C)
	{
		ft_printf("Error\nMap invalide");
		return(-1);
	}
	return(0);
}

void	ft_collect(t_data *data)
{
	int i;

	i = 0;
	while(i < data->check_C)
	{
		if(data->perso->instances[0].y == data->col->instances[i].y && data->perso->instances[0].x == data->col->instances[i].x)
			data->col->instances[i].enabled = false;
		i++;
	}
	// if (i == data->check_C)
	// 	collect_to_window(data);
}

void    hook(mlx_key_data_t keydata, void *param)
{
    t_data *data;

    data = param;
    (void)keydata;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        if(data->map.maps[(data->perso->instances[0].y / 64) - 1][data->perso->instances[0].x / 64] != '1')
        {
            data->perso->instances[0].y -= 64;
            data->foot_count++;
            ft_printf("Vous avez fait %d pas\n", data->foot_count);
        }
		ft_collect(data);
	}
    else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        if(data->map.maps[(data->perso->instances[0].y / 64) + 1][(data->perso->instances[0].x / 64)] != '1')
        {
            data->perso->instances[0].y += 64;
            data->foot_count++;
            ft_printf("Vous avez fait %d pas\n", data->foot_count);
        }
		ft_collect(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        if(data->map.maps[(data->perso->instances[0].y / 64)][(data->perso->instances[0].x / 64) - 1] != '1')
        {
            data->perso->instances[0].x -= 64;
            data->foot_count++;
            ft_printf("Vous avez fait %d pas\n", data->foot_count);
        }
		ft_collect(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        if(data->map.maps[data->perso->instances[0].y / 64][(data->perso->instances[0].x / 64) + 1] != '1')
        {
            data->perso->instances[0].x += 64;
            data->foot_count++;
            ft_printf("Vous avez fait %d pas\n", data->foot_count);
        }
		ft_collect(data);
    }
}

int	open_window(t_data *data)
{
	ft_init(data, data->map);
	image_to_window(data, &data->map);
	mlx_image_to_window(data->mlx, data->perso, (64 * data->P_position.y), (64 * data->P_position.x));
	mlx_key_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}


int main(int argc, char **argv)
{
	int fd;
	t_map map;
	t_data data;

	
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
	map.maps = map_read(fd, &map);
	set_data(&data, map);
	ft_printf("%s\n", data.map.maps[0]);
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
	if (flood_fill(data, &map, argv[1]) == -1)
		return(-1);
	ft_printf("ca marche\n");
	open_window(&data);
	return (0);
}