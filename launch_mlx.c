#include "fdf.h"

/*DDA*/
void draw_line(int X0, int Y0, int X1, int Y1, mlx_image_t *g_img) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) { 
    	mlx_put_pixel(g_img, round(X), round(Y), 0xFFFFFFFF);
        //putpixel(round(X), round(Y), RED); // put pixel at (X,Y) 
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
        usleep(100); // for visualization of line- 
                    // generation step by step 
    } 
} 

void	draw_image(t_screen *scrn, mlx_image_t *g_img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < (scrn->x_max * scrn->y_max))
	{
		j = i + 1;
		if (((i + 1) % scrn->x_max))
			draw_line(scrn->iso[i].x, scrn->iso[i].y, scrn->iso[j].x, scrn->iso[j].y, g_img);
		i ++;
	}
	i = 0;
	while (i < (scrn->x_max * scrn->y_max) - scrn->x_max)
	{
		j = i + scrn->x_max;
		draw_line(scrn->iso[i].x, scrn->iso[i].y, scrn->iso[j].x, scrn->iso[j].y, g_img);
		i ++;
	}
}


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
    draw_image(map, g_img);
    mlx_image_to_window(mlx, g_img, 100, HEIGHT/3);  // Adds an image to the render queue.
	ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
	// Connect the dots here
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img); // Once the application request an exit, cleanup.
	ft_printf("... fdf shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}