#include "fdf.h"
#include <stdio.h>

/*
void draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}*/

void make_pixel(uint8_t* pixel, uint32_t color)
{
	printf("\ncolor: %d\n", color);
	printf("\npixel: %d\n", *(pixel));
	*(pixel++) = (uint8_t)(color >> 24);
	//printf("color: %d\n", color);
	//printf("pixel: %d\n", *(pixel));
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

/*
mlx_image_t *draw_line(int X0, int Y0, int X1, int Y1, mlx_image_t *g_img) 
{ 
    // calculate dx & dy 
    uint8_t* pixelstart;
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
		pixelstart= &g_img->pixels[((int)round(Y) * g_img->width + (int)round(X)) * sizeof(int32_t)];
		draw_pixel(pixelstart, 0xFFFFFFFF);
    	//mlx_put_pixel(g_img, round(X), round(Y), 0xFFFFFFFF);
        //putpixel(round(X), round(Y), RED); // put pixel at (X,Y) 
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
        //usleep(100); // for visualization of line- 
                    // generation step by step 
    } 
    return (g_img);
} */

mlx_image_t *draw_line(int x0, int y0, int x1, int y1, mlx_image_t *g_img) 
{
	(void)x0;
	(void)y0;
	(void)x1;
	(void)y1;
	return (g_img);
}

mlx_image_t *draw_image(t_screen *scrn, mlx_image_t *g_img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < (scrn->x_max * scrn->y_max))
	{
		j = i + 1;
		if (((i + 1) % scrn->x_max))
			g_img=draw_line(scrn->iso[i].x, scrn->iso[i].y, scrn->iso[j].x, scrn->iso[j].y, g_img);
		i ++;
	}
	i = 0;
	while (i < (scrn->x_max * scrn->y_max) - scrn->x_max)
	{
		j = i + scrn->x_max;
		g_img=draw_line(scrn->iso[i].x, scrn->iso[i].y, scrn->iso[j].x, scrn->iso[j].y, g_img);
		i ++;
	}
	return(g_img);
}


/*
void draw_verts(t_screen *scrn, mlx_image_t *g_img)
{
	int i;

	i = 0;
	while (i < (scrn->y_max * scrn->x_max))
	{
		//if (scrn->iso[i].x <= WIDTH && scrn->iso[i].y <= HEIGHT && (scrn->iso[i].x >= 0 && scrn->iso[i].y >= 0))
		{
			mlx_put_pixel(g_img, round(scrn->iso[i].x), round(scrn->iso[i].y), 0xFFFFFFFF);
		}
		i ++;
	}
}
*/
/*
void draw_verts(t_screen *scrn, mlx_image_t *g_img)
{
	int i;

	i = 0;
	while (i < (scrn->y_max * scrn->x_max))
	{
		//if (scrn->iso[i].x <= WIDTH && scrn->iso[i].y <= HEIGHT && (scrn->iso[i].x >= 0 && scrn->iso[i].y >= 0))
		{
			mlx_put_pixel(g_img, round(scrn->iso[i].x), round(scrn->iso[i].y), 0xFFFFFFFF);
		}
		i ++;
	}
}
*/
void print_image_details(mlx_image_t *g_img)
{
	printf("g_img->width: %d\n",g_img->width);
	printf("g_img->height: %d\n",g_img->height);
	printf("element->count: %zu\n",g_img->count);
	printf("element->enabled: %d\n",g_img->enabled);
	printf("pixels:\n");
	int i = 0;
	while (i < 20)
	{
		printf("g_img->pixels[%i]: %x\n",i, g_img->pixels[i]);
		i ++;
	}
	printf("instances:\n");
	i = 0;
	while (i < 20)
	{
		if (g_img->instances != NULL)
		{
			printf("g_img->instances.x[%i]: %d\n",i, g_img->instances[i].x);
			printf("g_img->instances.y[%i]: %d\n",i, g_img->instances[i].y);
			printf("g_img->instances.z[%i]: %d\n",i, g_img->instances[i].z);
		}
		i ++;
	}
	//printf("g_img->pixels[i]: %i\n", g_img->pixels[1]);
}

//print_image_details(g_img);

mlx_image_t *draw_dots_to_image(mlx_image_t *g_img, t_screen *scrn)
{
	int i = 0;
	int x = 0;
	int y = 0;
	uint8_t* pixelstart;
	while (i < (scrn->x_max * scrn->y_max))
	{
		x = (scrn->iso[i].x);
		y = (scrn->iso[i].y);
		if (x >= scrn->z_min && y >= scrn->z_max && y <= HEIGHT - HEIGHT/3 && x <= WIDTH - WIDTH/5)
		{
			//pixelstart= &g_img->pixels[(y * g_img->width + x) * sizeof(int32_t)];
			pixelstart= &g_img->pixels[(y * g_img->width + x) * sizeof(int32_t)];
			printf("(%d,%d) ,",x, y);
			printf("(%f,%f) ,",scrn->iso[i].x, scrn->iso[i].y);
			//mlx_put_pixel(g_img, x, y, 0xFFFFFFFF);
			//mlx_put_pixel(g_img, (scrn->iso[i].x), scrn->iso[i].y, 0xFFFFFFFF);
			//draw_pixel(pixelstart, 0xFFFFFFFF);
			make_pixel(pixelstart, 0xFADD8E6);
		}
		i ++;
	}
	/**
 * Sets / puts a pixel onto an image.
 * 
 * NOTE: It is considered undefined behaviour when putting a pixel 
 * beyond the bounds of an image.
 * 
 * @param[in] image The MLX instance handle.
 * @param[in] x The X coordinate position.
 * @param[in] y The Y coordinate position.
 * @param[in] color The color value to put.
 */
//void mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);
	return (g_img);
}

int launch_mlx_window(t_screen	*map)
{
	mlx_t *mlx; // mlx.display = display
	mlx_image_t *g_img;
	
	mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);   // Creates a new image.

	g_img = draw_dots_to_image(g_img, map);
	printf("\ng_img->width: %d\n",g_img->width);
	printf("\ng_img->height: %d\n",g_img->height);
    //g_img = draw_image(map, g_img);
    mlx_image_to_window(mlx, g_img, WIDTH/5, HEIGHT/3);  // Adds an image to the render queue.
    //draw_verts(map, g_img);
    //draw_image(map, g_img);
    //mlx_image_to_window(mlx, g_img, 100, HEIGHT/3);  // Adds an image to the render queue.
	ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
	// Connect the dots here
	mlx_loop(mlx);
	//free(g_img->pixels);
	mlx_delete_image(mlx, g_img); // Once the application request an exit, cleanup.
	ft_printf("... fdf shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}