/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:34:09 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/16 16:37:10 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	remove_stuff_exit(t_screen *scrn, int code)
{
	mlx_delete_image (scrn->mlx, scrn->g_img);
	mlx_terminate (scrn->mlx);
	free_coord(scrn->cord);
	free_vert(scrn->iso);
	free_screen (scrn);
	exit (code);
}

void	new_projection(t_screen *scrn, keys_t key)
{
	if (key == MLX_KEY_Z || key == MLX_KEY_Y || key == MLX_KEY_M)
	{
		mlx_delete_image (scrn->mlx, scrn->g_img);
		free_vert(scrn->iso);
		if (key == MLX_KEY_Z)
			fdf_init (scrn, 1);
		else if (key == MLX_KEY_Y)
			fdf_init (scrn, 2);
		scrn->g_img = mlx_new_image (scrn->mlx, WIDTH, HEIGHT);
		if (!scrn->g_img)
		{
			mlx_terminate (scrn->mlx);
			remove_stuff_exit (scrn, 1);
		}
		scrn->g_img = draw_image(scrn, scrn->g_img, 0, 0);
		if (mlx_image_to_window (scrn->mlx, scrn->g_img, 0, 0) < 0)
		{
			mlx_delete_image (scrn->mlx, scrn->g_img);
			mlx_terminate (scrn->mlx);
			remove_stuff_exit (scrn, 1);
		}
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *map)
{
	t_screen	*scrn;

	scrn = (t_screen *)map;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		remove_stuff_exit(scrn, 0);
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		new_projection(map, MLX_KEY_Z);
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_PRESS)
		new_projection(map, MLX_KEY_Y);
}
