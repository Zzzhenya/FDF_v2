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

void	my_keyhook(mlx_key_data_t keydata, void *map)
{
	t_screen	*scrn;

	scrn = (t_screen *)map;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_delete_image (scrn->mlx, scrn->g_img);
		mlx_terminate (scrn->mlx);
		free_coord(scrn->cord);
		free_vert(scrn->iso);
		free_screen (scrn);
		exit (0);
	}
}
