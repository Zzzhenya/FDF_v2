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

t_screen	*init_screen(t_screen	*scrn)
{
	scrn = malloc (sizeof (t_screen));
	if (!scrn)
		return (0);
	scrn->a = 35.264 * M_PI / 180;
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
	return (scrn);
}

int	main(int argc, char **argv)
{
	t_screen	*scrn;

	scrn = NULL;
	if (argc != 2)
	{
		ft_printf ("	Usage: ./fdf *.fdf\n");
		return (1);
	}
	scrn = init_screen (scrn);
	if (!scrn)
		ft_errexit("t_screen init error");
	parse_and_store (scrn, argv[1]);
	fdf_init (scrn);
	print_t_cord(scrn);
	launch_mlx_window(scrn);
	free_coord(scrn->cord);
	free_vert(scrn->iso);
	free_screen (scrn);
	return (0);
}
