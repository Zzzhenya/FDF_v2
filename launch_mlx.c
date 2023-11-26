#include "fdf.h"

void draw_verts(t_screen *scrn, mlx_image_t *g_img)
{
	int i;

	i = 0;
	while (i < (scrn->y_max * scrn->x_max))
	{
		//if (scrn->iso[i].x <= WIDTH && scrn->iso[i].y <= HEIGHT && (scrn->iso[i].x >= 0 && scrn->iso[i].y >= 0))
		{
			mlx_put_pixel(g_img, scrn->iso[i].x, scrn->iso[i].y, 0xFFFFFFFF);
		}
		i ++;
	}
}

int launch_mlx_window(t_screen	*map)
{
	mlx_t *mlx; // mlx.display = display
	mlx_image_t *g_img;
	
	mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);   // Creates a new image.
	//mlx_image_to_window(mlx, g_img, WIDTH* 2/5, HEIGHT * 2/5);  // Adds an image to the render queue.
    draw_verts(map, g_img);
    //draw_image(map, g_img);
    mlx_image_to_window(mlx, g_img, 300, 200);  // Adds an image to the render queue.
	ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
	// Connect the dots here
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img); // Once the application request an exit, cleanup.
	ft_printf("... fdf shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}