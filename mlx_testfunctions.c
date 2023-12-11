/*
void draw_verts(t_screen *scrn, mlx_image_t *g_img)
{
	int i;

	i = 0;
	while (i < (scrn->y_max * scrn->x_max))
	{
		//if (scrn->iso[i].x <= WIDTH && scrn->iso[i].y\
		 <= HEIGHT && (scrn->iso[i].x >= 0 && scrn->iso[i].y >= 0))
		{
			mlx_put_pixel(g_img, round(scrn->iso[i].x), r\
			ound(scrn->iso[i].y), 0xFFFFFFFF);
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
void	print_image_details(mlx_image_t *g_img)
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

mlx_image_t	*draw_dots_to_image(mlx_image_t *g_img, t_screen *scrn)
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
*/

/*uint8_t*	pixelstart;
pixelstart = &g_img->pixels[(y * g_img->width + x) * sizeof(int32_t)];
make_pixel (pixelstart, 0xFADD8E6); */