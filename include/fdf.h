#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_vert
{
	float 		x;
	float 		y;
}				t_vert;

typedef struct s_cord
{
	int 		x;
	int 		y;
	int 		z;
}				t_cord;

typedef struct	s_screen
{
	int 	x_max;
	int 	y_max;
	int 	z_max;
	float  		a;
	float 		b;
	t_cord	*cord;
	t_vert	*iso;
}				t_screen;

/* debug_utils.c */

void free_coord(t_cord	*cord);
void free_vert(t_vert *iso);
void free_screen(t_screen *scrn);
void print_screen_details(t_screen *scrn);

#endif