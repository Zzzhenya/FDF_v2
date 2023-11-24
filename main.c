#include "fdf.h"
#include <stdio.h>

t_screen *init_screen(t_screen	*scrn)
{
	scrn = malloc (sizeof (t_screen));
	if (!scrn)
		return (0);
	scrn->a = 35.264 * M_PI/180;
	scrn->b = 45 * M_PI/180;
	scrn->x_max = 0;
	scrn->y_max = 0;
	scrn->z_max = 0;
	return (scrn);
}

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

int main(int argc, char **argv)
{
	t_screen	*scrn;

	scrn = NULL;
	if (argc != 2)
	{
		ft_printf("	Usage: ./fdf map.fdf\n");
		return (1);
	}
	ft_printf("file: %s\n", argv[1]);
	scrn = init_screen(scrn);
	if (!scrn)
		ft_errexit("t_screen init error");
	print_screen_details(scrn);
	free_screen(scrn);
	return(0);
}