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

#endif