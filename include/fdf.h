/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:30:56 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/11 19:30:59 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# define WIDTH 1024
# define HEIGHT 640	

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
	float		x;
	float		y;
	float		z;
}				t_vert;

typedef struct s_cord
{
	int			x;
	int			y;
	int			z;
}				t_cord;

typedef struct s_screen
{
	int			x_max;
	int			y_max;
	float		y_height;
	float		x_width;
	float		x_min;
	float		y_min;
	float		scale;
	float		a;
	float		b;
	t_line		line;
	t_cord		*cord;
	t_vert		*iso;
	mlx_t		*mlx;
	mlx_image_t	*g_img;
}				t_screen;

/* debug_utils.c */

void		free_coord(t_cord	*cord);
void		free_vert(t_vert *iso);
void		free_screen(t_screen *scrn);
void		free_arr(char **arr);

/* parse_and_store.c */

void		parse_and_store(t_screen *scrn, char *name);
void		store_3d_cords(t_screen *scrn, int fd, int i, int rows);

/* parser_utils.c */
int			ft_strstr(const char *haystack, const char *needle);
void		check_for_shape(int fd, t_screen *map);
void		get_map_dims(int fd, t_screen *scrn, int i);

/* fdf_init.c */

void		fdf_init(t_screen *scrn);
void		find_screen_limits(t_screen *scrn);

/* launc_mlx.c */

int			launch_mlx_window(t_screen	*map, char *file_name);

/* print.c */
void		print_t_cord(t_screen *map);
void		print_t_vert(t_screen *map);
void		print_screen_details(t_screen *scrn);
void		print_arr(char **arr);

/* bresenham.c */
void		make_pixel(uint8_t *pixel, uint32_t color);
mlx_image_t	*line_helper(t_line *line, mlx_image_t *g_img, t_screen *scrn);
mlx_image_t	*draw_line(t_line *line, mlx_image_t *g_img, t_screen *scrn);
mlx_image_t	*draw_image(t_screen *scrn, mlx_image_t *g_img, int i, int j);

/* hooks.c */
void		my_keyhook(mlx_key_data_t keydata, void *scrn);

/* project.c */
t_screen	*setup_vert(t_screen *scrn, int i);
t_screen	*rot_on_y(t_screen *scrn, int i, float b);
t_screen	*rot_on_z(t_screen *scrn, int i, float b);
t_screen	*rot_on_x(t_screen *scrn, int i, float a);
t_screen	*ortho(t_screen *scrn, int i);

#endif
