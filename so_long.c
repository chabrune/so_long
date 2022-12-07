#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 1680
#define HEIGHT 1200

mlx_image_t *img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		img->instances[0].y -= 20;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		img->instances[0].y += 20;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		img->instances[0].x -= 20;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		img->instances[0].x += 20;
}

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{


	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();
	// Try to load the file
	mlx_texture_t* xpm = mlx_load_png("PNG/perso.png");
	if (!xpm)
        error();   
	// Convert texture to a displayable image
	img = mlx_texture_to_image(mlx, xpm);
	if (!img)
        error();

	// Display the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();
        mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	// Optional, terminate will clean up any left overs, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_delete_texture(xpm);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}