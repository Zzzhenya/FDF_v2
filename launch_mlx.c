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
	make_line_zero(&scrn->line);
	while (i < (scrn->x_max * scrn->y_max))
	{
		j = i + 1;
		if (j % scrn->x_max)
		{
			set_values (&scrn->line, scrn, i, j);
			g_img = draw_line(&scrn->line, g_img, scrn);
		}
		i ++;
	}
	i = 0;
	while (i < (scrn->x_max * scrn->y_max) - scrn->x_max)
	{
		j = i + scrn->x_max;
		set_values (&scrn->line, scrn, i, j);
		g_img = draw_line(&scrn->line, g_img, scrn);
		i ++;
	}
	return (g_img);
}

int	launch_mlx_window(t_screen	*map, char *file_name)
{
	map->mlx = mlx_init (WIDTH, HEIGHT, file_name, true);
	if (!map->mlx)
		return (-1);
	map->g_img = mlx_new_image (map->mlx, WIDTH, HEIGHT);
	if (!map->g_img)
	{
		mlx_terminate (map->mlx);
		return (-1);
	}
	map->g_img = draw_image (map, map->g_img, 0, 0);
	if (mlx_image_to_window (map->mlx, map->g_img, 0, 0) < 0)
	{
		mlx_delete_image (map->mlx, map->g_img);
		mlx_terminate (map->mlx);
		return (-1);
	}
	mlx_key_hook(map->mlx, &my_keyhook, map);
	mlx_loop (map->mlx);
	mlx_delete_image (map->mlx, map->g_img);
	mlx_terminate (map->mlx);
	return (0);
}
