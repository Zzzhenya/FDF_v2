#include "fdf.h"
#include <stdio.h>
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
	int 	i;
	t_cord *cord;

	i = 0;
	cord = map->cord;
	while (i < map->x_max * map->y_max)
	{
		cord[i].x = 0;
		cord[i].z = 0;
		cord[i].y = 0;
		//free(&cord[i]);
		i ++;
	}
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
		ft_printf("%d,(%d,%d,%d)\n", i,
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