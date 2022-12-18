/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:07 by chabrune          #+#    #+#             */
/*   Updated: 2022/12/13 16:44:31 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**map_read(int fd)
{
	t_list *list;
	char **maps;
		
}

	

int main(int argc, char **argv)
{
	int fd;
	char **maps;

	(void)argv;
	if (argc != 2)
	{
		printf("Error\n Nombre d'argument invalide");
		return (-1);
	}
	else
	{
		fd = open("MAPS/maps.ber", O_RDONLY);
		maps = map_read(fd);
	}
}
