#include "so_long.h"

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

void	ft_collect(t_data *data)
{
	int i;

	i = 0;
	while(i < 1000)
	{
		
		if(data->perso->instances[0].y == data->col->instances[i].y 
		&& data->perso->instances[0].x == data->col->instances[i].x 
		&& data->col->instances[i].enabled)
		{
			data->col->instances[i].enabled = false;
			data->check_C--;
		}
		i++;
		if (data->perso->instances[0].y / 64 == data->exit->instances[0].y && data->perso->instances[0].x / 64 == data->exit->instances[0].x && data->check_C == 0)
			mlx_close_window(data->mlx);
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