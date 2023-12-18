/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:34:29 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/16 16:34:39 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_3d_cords(t_screen *map)
{
	t_cord	*cord;

	cord = map->cord;
	free (cord);
	cord = NULL;
	ft_printf("...Grid cleared.\n");
}

/*Free array when parsing fails*/
void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free (arr[i]);
		arr[i] = NULL;
		i ++;
	}
	free (arr);
	arr = NULL;
}

void	free_coord(t_cord	*cord)
{
	free (cord);
	cord = NULL;
}

void	free_vert(t_vert *iso)
{
	free (iso);
	iso = NULL;
}

void	free_screen(t_screen *scrn)
{
	scrn->a = 0;
	scrn->b = 0;
	scrn->x_max = 0;
	scrn->y_max = 0;
	scrn->x_min = 0;
	scrn->y_min = 0;
	scrn->scale = 0;
	scrn->x_width = 0;
	scrn->y_height = 0;
	scrn->iso = NULL;
	scrn->cord = NULL;
	scrn->mlx = NULL;
	scrn->g_img = NULL;
	free (scrn);
	scrn = NULL;
}
