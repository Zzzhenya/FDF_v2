/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:36:11 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/16 16:36:30 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

static void	consider_pixel(t_screen *scrn, int x, int y, mlx_image_t *g_img)
{
	uint8_t	*pixelstart;
	int		size;

	pixelstart = NULL;
	size = round(scrn->line.y0 * g_img->width + scrn->line.x0);
	if (round(x) >= 0 && round(y) >= 0 && size < HEIGHT * WIDTH)
	{
		if (round(y) <= HEIGHT && round(x) <= WIDTH)
		{
			pixelstart = &g_img->pixels[size * sizeof(int32_t)];
			make_pixel (pixelstart, 0xFFFFFFFF);
		}
	}
}

mlx_image_t	*line_helper(t_line *line, mlx_image_t *g_img, t_screen *scrn)
{
	while (1)
	{
		consider_pixel(scrn, line->x0, line->y0, g_img);
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
	g_img = line_helper (line, g_img, scrn);
	return (g_img);
}
