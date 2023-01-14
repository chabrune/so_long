#include "so_long.h"

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
	free(mapff);
	return(0);
}

