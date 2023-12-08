#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

# define WIDTH 1024
# define HEIGHT 750

typedef struct s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			e;
	int			e2;
}				t_line;

typedef struct s_vert
{
	float 		x;
	float 		y;
	float		z;
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
	int  	z_min;
	int  	scale;
	float  		a;
	float 		b;
	float 		c;
	t_cord	*cord;
	t_vert	*iso;
}				t_screen;

/* debug_utils.c */

void	free_coord(t_cord	*cord);
void	free_vert(t_vert *iso);
void	free_screen(t_screen *scrn);
void	print_screen_details(t_screen *scrn);
void	free_arr(char **arr);
void	print_t_cord(t_screen *map);
void	print_t_vert(t_screen *map);
//void 	clear_3d_cords(t_screen  *map);


/* parse_and_store.c */

int parse_and_store(t_screen *scrn, char *name);
int	store_3d_cords(t_screen *map, int fd, int i);

/* parser_utils.c */
int	ft_strstr(const char *haystack, const char *needle);
void	check_for_shape(int fd, t_screen *map);
void get_map_dims(int fd, t_screen *scrn, int i);

/* fdf_init.c */

void	fdf_init(t_screen *scrn);

/* launc_mlx.c */

int launch_mlx_window(t_screen	*map);

#endif