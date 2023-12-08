#include "fdf.h"
#include <stdio.h>

void make_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

/* Bresenham's Line Algorithm */
mlx_image_t *draw_line(t_line *line, mlx_image_t *g_img) 
{
	uint8_t*	pixelstart;
	int x = 0;
	int y = 0;
	float m = 0;

	m = (line->y1 - line->y0) / (line->x1 - line->x0);
	for (x = line->x0; x <= line->x1; x++) {  
        y = round(m*x);
        if (x <= WIDTH && y <= HEIGHT && (x >= 0 && y >= 0))
        {
			pixelstart = &g_img->pixels[(y * g_img->width + x) * sizeof(int32_t)];
			make_pixel (pixelstart, 0xFADD8E6);
		}
	}

	return (g_img);
}
//uint8_t*	pixelstart;
//pixelstart = &g_img->pixels[(y * g_img->width + x) * sizeof(int32_t)];
//make_pixel (pixelstart, 0xFADD8E6);

void make_line_zero(t_line *line)
{
	line->x0 = 0;
	line->y0 = 0;
	line->x1 = 0;
	line->y1 = 0;
	line->dx = 0;
	line->dy = 0;
	line->sx = 0;
	line->sy = 0;
	line->e = 0;
	line->e2 = 0;
}


mlx_image_t *draw_image(t_screen *scrn, mlx_image_t *g_img)
{
	int 	i;
	int 	j;
	t_line	line;

	i = 0;
	j = 0;
	make_line_zero(&line);
	while (i < (scrn->x_max * scrn->y_max))
	{
		j = i + 1;
		if (((i + 1) % scrn->x_max))
		{
			line.x0 = scrn->iso[i].x;
			line.y0 = scrn->iso[i].y;
			line.x1 = scrn->iso[j].x;
			line.y1 = scrn->iso[j].y;
			g_img=draw_line(&line, g_img);
		}
		i ++;
	}
	i = 0;
	while (i < (scrn->x_max * scrn->y_max) - scrn->x_max)
	{
		j = i + scrn->x_max;
		line.x0 = scrn->iso[i].x;
		line.y0 = scrn->iso[i].y;
		line.x1 = scrn->iso[j].x;
		line.y1 = scrn->iso[j].y;
		//g_img=draw_line(&line, g_img);
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

mlx_image_t *draw_dots_to_image(mlx_image_t *g_img, t_screen *scrn)
{
	int			i;
	int			x;
	int			y;
	uint8_t*	pixelstart;

	i = 0;
	x = 0;
	y = 0;
	while (i < (scrn->x_max * scrn->y_max))
	{
		x = (scrn->iso[i].x);
		y = (scrn->iso[i].y);
		if (x >= scrn->z_min && y >= scrn->z_max && y <= HEIGHT - HEIGHT/3 && x <= WIDTH - WIDTH/5)
		{
			pixelstart = &g_img->pixels[(y * g_img->width + x) * sizeof(int32_t)];
			make_pixel (pixelstart, 0xFADD8E6);
			printf("%d: pixp: %p\n",i, pixelstart);
			printf("%d: pixd: %p\n",i, &g_img->pixels[(y * g_img->width + x) * sizeof(int32_t)]);
		}
		i ++;
	}
	return (g_img);
}

int launch_mlx_window(t_screen	*map)
{
	mlx_t		*mlx;
	mlx_image_t	*g_img;
	
	mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);   // Creates a new image.

	//g_img = draw_dots_to_image(g_img, map);
	//printf("\ng_img->width: %d\n",g_img->width);
	//printf("\ng_img->height: %d\n",g_img->height);
    g_img = draw_image(map, g_img);
    mlx_image_to_window(mlx, g_img, WIDTH/5, HEIGHT/3);  // Adds an image to the render queue.
    //draw_verts(map, g_img);
    //draw_image(map, g_img);
    //mlx_image_to_window(mlx, g_img, 100, HEIGHT/3);  // Adds an image to the render queue.
	//ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
	// Connect the dots here
	mlx_loop(mlx);
	//free(g_img->pixels);
	mlx_delete_image(mlx, g_img); // Once the application request an exit, cleanup.
	ft_printf("... fdf shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}