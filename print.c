/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:32:32 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/16 16:32:41 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_t_vert(t_screen *map)
{
	int	i;

	i = 0;
	while (i < map->x_max * map->y_max)
	{
		ft_printf ("vert: %d,(%d,%d,%d)\n", i,
			map->iso[i].x,
			map->iso[i].y,
			map->iso[i].z);
		i ++;
	}
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf ("%d :%s\n", i, arr[i]);
		i ++;
	}
}

void	print_t_cord(t_screen *map)
{
	int	i;

	i = 0;
	while (i < map->x_max * map->y_max)
	{
		ft_printf("cord: %d,(%d,%d,%d)\n", i,
			map->cord[i].x,
			map->cord[i].y,
			map->cord[i].z);
		i ++;
	}
}

void	print_screen_details(t_screen *scrn)
{
	ft_printf("alpha: %d\n", scrn->a);
	ft_printf("beta: %d\n", scrn->b);
	ft_printf("x_max :%d\n", scrn->x_max);
	ft_printf("y_max :%d\n", scrn->y_max);
	ft_printf("ymin :%d\n", scrn->y_min);
	ft_printf("xmin :%d\n", scrn->x_min);
	if (scrn->cord)
		print_t_cord(scrn);
	if (scrn->iso)
		print_t_vert(scrn);
}
