/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:04 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/07 18:22:12 by chabrune         ###   ########.fr       */
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
    int check_C;
	int check_E;
	int check_P;
    int foot_count;
    int C_count;
    t_map map;
    t_pos P_position;
} t_data;

char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);

#endif