/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:35:49 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/16 16:36:01 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_screen_cords(t_screen *scrn, int type)
{
	int	i;

	i = 0;
	scrn->iso = malloc (scrn->x_max * scrn->y_max * (sizeof(t_vert)));
	if (!scrn->iso)
	{
		free_coord (scrn->cord);
		free_screen (scrn);
		ft_errexit ("malloc failed.");
	}
	while (i < (scrn->y_max * scrn->x_max))
	{
		scrn = setup_vert (scrn, i);
		if (type == 2)
			scrn = rot_on_z (scrn, i, scrn->b);
		else
			scrn = rot_on_y (scrn, i, scrn->b);
		scrn = rot_on_x (scrn, i, scrn->a);
		scrn = ortho (scrn, i);
		scrn->iso[i].z = fabsf (scrn->iso[i].z);
		i ++;
	}
}

void	find_screen_limits(t_screen *scrn)
{
	int	i;

	i = 0;
	while (i < (scrn->x_max * scrn->y_max))
	{
		if (scrn->iso[i].x < scrn->x_min)
			scrn->x_min = scrn->iso[i].x;
		if (scrn->iso[i].y < scrn->y_min)
			scrn->y_min = scrn->iso[i].y;
		i ++;
	}
}

void	move(t_screen *scrn)
{
	int	i;

	i = 0;
	while (i < (scrn->x_max * scrn->y_max))
	{
		scrn->iso[i].x += (0 - scrn->x_min);
		scrn->iso[i].y += (0 - scrn->y_min);
		if (scrn->iso[i].x > scrn->x_width)
			scrn->x_width = scrn->iso[i].x;
		if (scrn->iso[i].y > scrn->y_height)
			scrn->y_height = scrn->iso[i].y;
		i ++;
	}
	scrn->x_min = 0;
	scrn->y_min = 0;
}

void	scale(t_screen *scrn)
{
	int		i;
	float	a;
	float	b;

	if (scrn->y_height >= HEIGHT)
		a = scrn->y_height - 1 / HEIGHT;
	else
		a = HEIGHT / scrn->y_height - 1;
	if (scrn->x_width - 1 >= WIDTH)
		b = scrn->x_width - 1 / WIDTH;
	else
		b = WIDTH / scrn->x_width - 1;
	if (a >= b)
		scrn->scale = b;
	else
		scrn->scale = a;
	i = 0;
	while (i < (scrn->y_max * scrn->x_max))
	{
		scrn->iso[i].x *= scrn->scale;
		scrn->iso[i].y *= scrn->scale;
		i ++;
	}
}

void	fdf_init(t_screen *scrn, int type)
{
	calc_screen_cords(scrn, type);
	find_screen_limits(scrn);
	move(scrn);
	scale(scrn);
}
