/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:05:46 by chabrune          #+#    #+#             */
/*   Updated: 2022/12/07 18:39:37 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img init_img(void *mlx)
{
    t_img rt;
    int		wid;
	int		hei;

	rt.land = mlx_load_png("./images/land.xpm");
    mlx_resize_image(rt.land, 60, 60);
    return(rt);
}