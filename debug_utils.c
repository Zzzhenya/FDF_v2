#include "fdf.h"

/*
void	free_stuff(t_screen *scrn)
{
	clear_3d_cords(scrn->map.cord, &scrn->map);
	clear_2d_cords(&scrn->map);
}


static void clear_2d_cords(t_obj *map)
{
	int i;

	i = 0;
	while (i < map->x_max * map->y_max)
	{
		map->iso[i].x = 0;
		map->iso[i].y = 0;
		i ++;
	}
	free(map->iso);
	map->iso = NULL;
}
*/

void 	clear_3d_cords(t_screen  *map)
{
	t_cord *cord;

	cord = map->cord;
	free(cord);
	cord = NULL;
	ft_printf("...Grid cleared.\n");
}

void	print_t_cord(t_screen *map)
{
	int i;

	i = 0;
	//if (!map->cord)
	//	return ;
	while (i < map->x_max * map->y_max)
	{
		ft_printf("cord: %d,(%d,%d,%d)\n", i,
			map->cord[i].x,
			map->cord[i].y,
			map->cord[i].z);
		i ++;
	}
}


/*Free array when parsing fails*/
void	free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i ++;
	}
	free (arr);
	arr = NULL;
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
	scrn->a = 0;
	scrn->b = 0;
	scrn->c = 0;
	scrn->x_max = 0;
	scrn->y_max = 0;
	scrn->x_min = 0;
	scrn->y_min = 0;
	scrn->scale = 0;
	scrn->x_width = 0;
	scrn->y_height = 0;
	scrn->iso = NULL;
	scrn->cord = NULL;
	free (scrn);
	scrn = NULL;
}

void print_screen_details(t_screen *scrn)
{
	printf("alpha: %f\n", scrn->a);
	printf("beta: %f\n", scrn->b);
	ft_printf("x_max :%d\n", scrn->x_max);
	ft_printf("y_max :%d\n", scrn->y_max);
	ft_printf("ymin :%d\n", scrn->y_min);
	ft_printf("xmin :%d\n", scrn->x_min);
	if (scrn->cord)
		print_t_cord(scrn);
	if (scrn->iso)
		print_t_vert(scrn);
}

void	print_t_vert(t_screen *map)
{
	int i;

	i = 0;
	while (i < map->x_max * map->y_max)
	{
		printf ("vert: %d,(%f,%f,%f)\n", i,
			map->iso[i].x,
			map->iso[i].y,
			map->iso[i].z);
		i ++;
	}
}