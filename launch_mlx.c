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
	if (!mlx)
		return(-1);
	g_img = mlx_new_image (mlx, WIDTH, HEIGHT);
	if (!g_img)
	{
		mlx_terminate (mlx);
		return (-1);
	}
	g_img = draw_image (map, g_img, 0, 0);
	if (!g_img)
	{
		mlx_terminate (mlx);
		return (-1);
	}
	if (mlx_image_to_window (mlx, g_img, 0, 0) < 0)
	{
		mlx_delete_image (mlx, g_img);
		mlx_terminate (mlx);
		return (-1);
	}
	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop (mlx);
	mlx_delete_image (mlx, g_img);
	ft_printf ("... fdf closed.\n");
	mlx_terminate (mlx);
	mlx = NULL;
	g_img = NULL;
	return (0);
}
