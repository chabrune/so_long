#include "so_long.h"

void    hook(mlx_key_data_t keydata, void *param)
{
    t_data *data;

    data = param;
    (void)keydata;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		ft_key_W(data);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		ft_key_S(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		ft_key_A(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		ft_key_D(data);

}

void   ft_key_W(t_data *data)
{
	int x;
	int y;

   x = data->perso->instances[0].x / 64;
   y = data->perso->instances[0].y / 64;
   if(data->map.maps[y - 1][x] != '1')
    {
        data->perso->instances[0].y -= 64;
        data->foot_count++;
        ft_printf("Vous avez fait %d pas\n", data->foot_count);
        if (x != data->perso->instances[0].x / 64 || y != data->perso->instances[0].y / 64)
            ft_collect(data);
		if (data->map.maps[(data->perso->instances[0].y / 64)][data->perso->instances[0].x / 64] == 'E' && data->check_C == 0)
			mlx_close_window(data->mlx);
    }
}


void   ft_key_S(t_data *data)
{
	int x;
	int y;

   x = data->perso->instances[0].x / 64;
   y = data->perso->instances[0].y / 64;
   if(data->map.maps[y + 1][x] != '1')
    {
        data->perso->instances[0].y += 64;
        data->foot_count++;
        ft_printf("Vous avez fait %d pas\n", data->foot_count);
        if (x != data->perso->instances[0].x / 64 || y != data->perso->instances[0].y / 64)
            ft_collect(data);
		if (data->map.maps[(data->perso->instances[0].y / 64)][data->perso->instances[0].x / 64] == 'E' && data->check_C == 0)
			mlx_close_window(data->mlx);
    }
}


void   ft_key_A(t_data *data)
{
	int x;
	int y;

   x = data->perso->instances[0].x / 64;
   y = data->perso->instances[0].y / 64;
   if(data->map.maps[y][x - 1] != '1')
    {
        data->perso->instances[0].x -= 64;
        data->foot_count++;
        ft_printf("Vous avez fait %d pas\n", data->foot_count);
        if (x != data->perso->instances[0].x / 64 || y != data->perso->instances[0].y / 64)
            ft_collect(data);
		if (data->map.maps[(data->perso->instances[0].y / 64)][data->perso->instances[0].x / 64] == 'E' && data->check_C == 0)
			mlx_close_window(data->mlx);
    }
}


void   ft_key_D(t_data *data)
{
	int x;
	int y;

   x = data->perso->instances[0].x / 64;
   y = data->perso->instances[0].y / 64;
   if(data->map.maps[y][x + 1] != '1')
    {
        data->perso->instances[0].x += 64;
        data->foot_count++;
        ft_printf("Vous avez fait %d pas\n", data->foot_count);
        if (x != data->perso->instances[0].x / 64 || y != data->perso->instances[0].y / 64)
            ft_collect(data);
		if (data->map.maps[(data->perso->instances[0].y / 64)][data->perso->instances[0].x / 64] == 'E' && data->check_C == 0)
			mlx_close_window(data->mlx);
    }
}