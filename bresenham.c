#include "fdf.h"

void	make_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

mlx_image_t	*line_helper(int x, int y, t_line *line, mlx_image_t *g_img, t_screen *scrn)
{
	uint8_t	*pixelstart;

	while (1)
	{
		x = line->x0; 
		y = line->y0;
		if (x >= scrn->x_min && y >= scrn->y_min)
		{
			if (y <= HEIGHT && x <= WIDTH)
			{
				pixelstart = &g_img->pixels[(y * g_img->width + x) \
				* sizeof(int32_t)];
				make_pixel (pixelstart, 0xFADD8E6);
			}
		}
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		line->e2 = line->e * 2;
		if (line->e2 >= line->dy)
		{
			if (line->x0 == line->x1)
				break ;
			line->e = line->e + line->dy;
			line->x0 = line->x0 + line->sx;
		}
		if (line->e2 <= line->dx)
		{
			if (line->y0 == line->y1)
				break ;
			line->e = line->e + line->dx;
			line->y0 = line->y0 + line->sy;
		}
	}
	return (g_img);
}

/* Bresenham's Line Algorithm */
mlx_image_t	*draw_line(t_line *line, mlx_image_t *g_img, t_screen *scrn)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	line->dx = abs (line->x1 - line->x0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	line->dy = -abs (line->y1 - line->y0);
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->e = line->dx + line->dy;
	g_img = line_helper (x, y, line, g_img, scrn);
	return (g_img);
}