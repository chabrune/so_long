#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_game
{
    int height;
    int width;
    t_img img;
    char *str_line;
    void *mlx;
    void *win;
    int all_coll;
    int coll_count;
    int walk_count;
}   t_game;

typedef struct s_img
{
    void *chara;
    void *chest;
    void *land;
    void *rune;
    void *rune2;
    void *wall;
}   t_img;

# include "../MLX42/MLX42.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

#endif