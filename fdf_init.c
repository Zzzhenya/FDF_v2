#include "fdf.h"

void rot_on_y(t_screen *scrn, int i, float b)
{
	scrn->iso[i].x = scrn->cord[i].x * cosf(b) - scrn->cord[i].z * sinf(b);
	scrn->iso[i].y = scrn->cord[i].y;
	scrn->iso[i].z = scrn->cord[i].x * sinf(b) + scrn->cord[i].z * cosf(b);
}

void rot_on_x(t_screen *scrn, int i, float a)
{
	scrn->iso[i].x = scrn->iso[i].x;
	scrn->iso[i].y = scrn->iso[i].y * cosf(a) + scrn->iso[i].z * sinf(a);
	scrn->iso[i].z = scrn->iso[i].z * cosf(a) - scrn->iso[i].y * sinf(a);
}

void ortho(t_screen *scrn, int i)
{
	scrn->iso[i].x = scrn->iso[i].x * 1;
	scrn->iso[i].y = scrn->iso[i].y * 1;
	scrn->iso[i].z = scrn->iso[i].z * 0;

}

void	calc_screen_cords(t_screen *scrn)
{
	int i;
	float a;
	float b;
	
	a = scrn->a;
	b = scrn->b;
	scrn->iso = malloc (scrn->x_max * scrn->y_max * (sizeof(t_vert)));
	if (!scrn->iso)
	{
		free_coord(scrn->cord);
		free_screen (scrn);
		ft_errexit("malloc failed.");
	}
	i = 0;
	while (i < scrn->y_max * scrn->x_max)
	{
		rot_on_y(scrn, i, b);
		rot_on_x(scrn, i, a);
		ortho(scrn, i);
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