/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:30:15 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/16 16:32:24 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_screen	*setup_vert(t_screen *scrn, int i)
{
	scrn->iso[i].x = scrn->cord[i].x;
	scrn->iso[i].y = scrn->cord[i].y;
	scrn->iso[i].z = scrn->cord[i].z;
	return (scrn);
}

t_screen	*rot_on_y(t_screen *scrn, int i, float b)
{
	float	x;
	float	y;
	float	z;

	x = scrn->iso[i].x;
	y = scrn->iso[i].y;
	z = scrn->iso[i].z;
	scrn->iso[i].x = x * cos(b) - z * sin(b);
	scrn->iso[i].y = y;
	scrn->iso[i].z = x * sin(b) + z * cos(b);
	return (scrn);
}

t_screen	*rot_on_z(t_screen *scrn, int i, float b)
{
	float	x;
	float	y;
	float	z;

	x = scrn->iso[i].x;
	y = scrn->iso[i].y;
	z = scrn->iso[i].z;
	scrn->iso[i].x = x * cos(b) - y * sin(b);
	scrn->iso[i].z = z;
	scrn->iso[i].y = x * sin(b) + y * cos(b);
	return (scrn);
}

t_screen	*rot_on_x(t_screen *scrn, int i, float a)
{
	float	x;
	float	y;
	float	z;

	x = scrn->iso[i].x;
	y = scrn->iso[i].y;
	z = scrn->iso[i].z;
	scrn->iso[i].x = x;
	scrn->iso[i].y = y * cos(a) + z * sin(a);
	scrn->iso[i].z = z * cos(a) - y * sin(a);
	return (scrn);
}

t_screen	*ortho(t_screen *scrn, int i)
{
	scrn->iso[i].x = scrn->iso[i].x * 1;
	scrn->iso[i].y = scrn->iso[i].y * -1;
	scrn->iso[i].z = scrn->iso[i].z * 0;
	return (scrn);
}
