/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:06:13 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/11 18:06:25 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	make_line_zero(t_line *line)
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

t_screen	*init_screen(t_screen	*scrn)
{
	scrn = malloc (sizeof (t_screen));
	if (!scrn)
		return (0);
	scrn->a = atan(sqrt(2));
	scrn->b = 45 * M_PI / 180;
	scrn->x_max = 0;
	scrn->y_max = 0;
	scrn->y_height = 0;
	scrn->x_width = 0;
	scrn->y_min = 0;
	scrn->x_min = 0;
	scrn->scale = 20;
	scrn->iso = NULL;
	scrn->cord = NULL;
	scrn->mlx = NULL;
	scrn->g_img = NULL;
	make_line_zero (&scrn->line);
	return (scrn);
}

int	main(int argc, char **argv)
{
	t_screen	*scrn;
	int			code;

	code = 0;
	scrn = NULL;
	if (argc != 2)
	{
		ft_printf ("Usage: ./fdf map.fdf\n");
		return (1);
	}
	scrn = init_screen (scrn);
	if (!scrn)
		ft_errexit("t_screen init error");
	parse_and_store (scrn, argv[1]);
	fdf_init (scrn);
	code = launch_mlx_window(scrn, argv[1]);
	free_coord(scrn->cord);
	free_vert(scrn->iso);
	free_screen (scrn);
	if (code != 0)
		ft_errexit ("MLX failed.");
	return (0);
}
