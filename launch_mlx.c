/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:34:40 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/11 19:34:42 by sde-silv         ###   ########.fr       */
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

/*if (x <= WIDTH && y <= HEIGHT && (x >= 0 && y >= 0))*/
mlx_image_t	*line_helper(int x, int y, t_line *line, mlx_image_t *g_img, t_screen *scrn)
{
	uint8_t	*pixelstart;

	while (1)
	{
		x = line->x0; 
		y = line->y0;
		if (x >= scrn->z_min && y >= scrn->z_max)
		{
			if (y <= HEIGHT - HEIGHT / 3 && x <= WIDTH - WIDTH / 5)
			{
				pixelstart = &g_img->pixels[(y * g_img->width + x) \
				* sizeof(int32_t)];
				make_pixel (pixelstart, 0xFADD8E6, scrn);
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
	line->dx = abs(line->x1 - line->x0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	line->dy = -abs(line->y1 - line->y0);
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->e = line->dx + line->dy;
	g_img = line_helper(x, y, line, g_img, scrn);
	return (g_img);
}

void	make_line_zero(t_line *line)
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

static void	set_values(t_line *line, t_screen *scrn, int i, int j)
{
	line->x0 = scrn->iso[i].x;
	line->y0 = scrn->iso[i].y;
	line->x1 = scrn->iso[j].x;
	line->y1 = scrn->iso[j].y;
}

mlx_image_t	*draw_image(t_screen *scrn, mlx_image_t *g_img, int i, int j)
{
	t_line	line;

	make_line_zero(&line);
	while (i < (scrn->x_max * scrn->y_max))
	{
		j = i + 1;
		if (j % scrn->x_max)
		{
			set_values (&line, scrn, i, j);
			g_img = draw_line(&line, g_img, scrn);
		}
		i ++;
	}
	i = 0;
	while (i < (scrn->x_max * scrn->y_max) - scrn->x_max)
	{
		j = i + scrn->x_max;
		set_values (&line, scrn, i, j);
		g_img = draw_line(&line, g_img, scrn);
		i ++;
	}
	return (g_img);
}

int	launch_mlx_window(t_screen	*map)
{
	mlx_t		*mlx;
	mlx_image_t	*g_img;

	mlx = mlx_init (WIDTH, HEIGHT, "Wireframe", true);
	g_img = mlx_new_image (mlx, WIDTH, HEIGHT);
	g_img = draw_image (map, g_img, 0, 0);
	mlx_image_to_window (mlx, g_img, WIDTH / 5, HEIGHT / 3);
	mlx_loop (mlx);
	mlx_delete_image (mlx, g_img);
	ft_printf ("... fdf closed. See you tomorrow!\n");
	mlx_terminate (mlx);
	return (0);
}
