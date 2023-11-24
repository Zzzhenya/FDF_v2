#include "fdf.h"
#include <stdio.h>

void free_coord(t_cord	*cord)
{
	free(cord);
	cord = NULL;
}

void free_vert(t_vert *iso)
{
	free(iso);
	iso = NULL;
}

void free_screen(t_screen *scrn)
{
	/*
	if (scrn->cord)
	{
		//free_coord(scrn->cord);
		//scrn->cord = NULL;
	}
	if (scrn->iso)
	{
		//free_vert(scrn->iso);
		//scrn->iso = NULL;
	}*/
	scrn->a = 0;
	scrn->b = 0;
	scrn->x_max = 0;
	scrn->y_max = 0;
	scrn->z_max = 0;
	free (scrn);
	scrn = NULL;
}

void print_screen_details(t_screen *scrn)
{
	printf("alpha: %f\n", scrn->a);
	printf("beta: %f\n", scrn->b);
	ft_printf("width :%d\n", scrn->x_max);
	ft_printf("height :%d\n", scrn->y_max);
	ft_printf("depth :%d\n", scrn->z_max);
}