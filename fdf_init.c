#include "fdf.h"

t_screen *rot_on_y(t_screen *scrn, int i, float b)
{
	scrn->iso[i].x = (float)scrn->cord[i].x * cos(b) - \
	(float)scrn->cord[i].z * sin(b);
	scrn->iso[i].y = scrn->cord[i].y;
	scrn->iso[i].z = (float)scrn->cord[i].x * sin(b) + \
	(float)scrn->cord[i].z * cos(b);
	return (scrn);
}

t_screen *rot_on_x(t_screen *scrn, int i, float a)
{
	scrn->iso[i].x = scrn->iso[i].x;
	scrn->iso[i].y = scrn->iso[i].y * cosf(a) + scrn->iso[i].z * sinf(a);
	scrn->iso[i].z = scrn->iso[i].z * cosf(a) - scrn->iso[i].y * sinf(a);
	return (scrn);
}

t_screen *ortho(t_screen *scrn, int i)
{
	scrn->iso[i].x = scrn->iso[i].x * 1;
	scrn->iso[i].y = scrn->iso[i].y * 1;
	scrn->iso[i].z = scrn->iso[i].z * 0;
	return (scrn);
}

void	calc_screen_cords(t_screen *scrn)
{
	int i;
	
	i = 0;
	scrn->iso = malloc (scrn->x_max * scrn->y_max * (sizeof(t_vert)));
	if (!scrn->iso)
	{
		free_coord(scrn->cord);
		free_screen (scrn);
		ft_errexit("malloc failed.");
	}
	while (i < (scrn->y_max * scrn->x_max))
	{
		scrn = rot_on_y(scrn, i, scrn->b);
		scrn = rot_on_x(scrn, i, scrn->a);
		scrn = ortho(scrn, i);
		/*
		map->iso[i].x = map->cord[i].x * fabs(cosf(a)) + \
		map->cord[i].y * fabs(cosf(a + 2)) + \
		map->cord[i].z * fabs(cosf(a - 2));
		map->iso[i].y = map->cord[i].x * fabs(sinf(a)) + \
		map->cord[i].y * fabs(sinf(a + 2)) + \
		map->cord[i].z * fabs(sinf(a - 2));
		*/
		scrn->iso[i].x *= scrn->scale;
		scrn->iso[i].y *= scrn->scale;
		i ++;
	}
	print_screen_details (scrn);
}


void	fdf_init (t_screen *scrn)
{
	calc_screen_cords(scrn);
}