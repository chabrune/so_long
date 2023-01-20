/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:04 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/20 17:47:50 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/MLX42.h"
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_map
{
	char		**maps;
	int			x;
	int			y;
}				t_map;

typedef struct s_data
{
	mlx_image_t	*perso;
	mlx_image_t	*wall;
	mlx_image_t	*land;
	mlx_image_t	*col;
	mlx_image_t	*exit;
	mlx_image_t	*all;
	int			check_C;
	int			check_E;
	int			check_P;
	char		**maps;
	int			x;
	int			y;
	t_map		map;
	int			foot_count;
	int			C_count;
	t_pos		P_position;
	mlx_t		*mlx;
}				t_data;

void			print_error(char *msg, t_data *data);
int				open_window(t_data *data);
void			ft_collect(t_data *data);
int				flood_fill(t_data data, t_map *map, char *path);
int				f_fill(char **mapff, int x, int y);
void			image_to_window(t_data *data, t_map *map);
void			hook(mlx_key_data_t keydata, void *param);
void			ft_init(t_data *data, t_map map);
int				check_error_name(char *s);
int				check_rectangular(char **maps, t_map map);
int				check_letter(t_data *data);
int				check_full_one(t_map map);
char			**map_read(int fd, t_map *map, t_data *data);
void			set_data(t_data *data, t_map map);
void			ft_key_w(t_data *data);
void			ft_key_a(t_data *data);
void			ft_key_d(t_data *data);
void			ft_key_s(t_data *data);
char			*ft_strdup(const char *s);
int				ft_strlen_sl(const char *str);
char			*ft_strchr(const char *s, int c);
int				check_p_position(t_data *data);
void			ft_putstr(char *s);

#endif