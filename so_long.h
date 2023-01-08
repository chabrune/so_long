/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:04 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/08 14:37:42 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/MLX42.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"

typedef struct s_map
{
    char **maps;
    int x;
    int y;
} t_map;

typedef struct s_pos
{
    int x;
    int y;
} t_pos;

typedef struct s_data
{
    mlx_image_t	*perso;
	mlx_image_t	*wall;
	mlx_image_t	*land;
	mlx_image_t	*col;
	mlx_image_t	*exit;
    mlx_image_t *all;
    int check_C;
	int check_E;
	int check_P;
    int foot_count;
    int C_count;
    t_map map;
    t_pos P_position;
    mlx_t   *mlx;
} t_data;

char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);

#endif