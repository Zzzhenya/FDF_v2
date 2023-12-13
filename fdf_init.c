#include "fdf.h"

t_screen	*setup_vert(t_screen *scrn, int i)
{
	scrn->iso[i].x = scrn->cord[i].x;
	scrn->iso[i].y = scrn->cord[i].y;
	scrn->iso[i].z = scrn->cord[i].z;
	return (scrn);
}


t_screen	*rot_on_y(t_screen *scrn, int i, float b)
{
	float x;
	float y;
	float z;

	x = scrn->iso[i].x;
	y = scrn->iso[i].y;
	z = scrn->iso[i].z;
	scrn->iso[i].x = x * cosf(b) - z * sinf(b);
	scrn->iso[i].y = y;
	scrn->iso[i].z = x * sinf(b) + z * cosf(b);
	return (scrn);
}

t_screen	*rot_on_z(t_screen *scrn, int i, float b)
{
	float x;
	float y;
	float z;

	x = scrn->iso[i].x;
	y = scrn->iso[i].y;
	z = scrn->iso[i].z;
	scrn->iso[i].x = x * cosf(b) - y * sinf(b);
	scrn->iso[i].z = z;
	scrn->iso[i].y = x * sinf(b) + y * cosf(b);
	return (scrn);
}

t_screen	*rot_on_x(t_screen *scrn, int i, float a)
{
	float x;
	float y;
	float z;

	x = scrn->iso[i].x;
	y = scrn->iso[i].y;
	z = scrn->iso[i].z;
	scrn->iso[i].x = x;
	scrn->iso[i].y = y * cosf(a) + z * sinf(a);
	scrn->iso[i].z = z * cosf(a) - y * sinf(a);
	return (scrn);
}

t_screen	*ortho(t_screen *scrn, int i)
{
	scrn->iso[i].x = scrn->iso[i].x * 1;
	scrn->iso[i].y = scrn->iso[i].y * -1;
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
		free_coord (scrn->cord);
		free_screen (scrn);
		ft_errexit ("malloc failed.");
	}
	while (i < (scrn->y_max * scrn->x_max))
	{
		scrn = setup_vert (scrn, i);
		
		scrn = rot_on_z (scrn, i, scrn->b);
		scrn = rot_on_x (scrn, i, scrn->a);
		scrn = ortho (scrn, i);
		scrn->iso[i].z = fabsf (scrn->iso[i].z);
		i ++;
	}
}

void	find_screen_limits(t_screen *scrn)
{
	int i;

	i = 0;
	while (i < (scrn->x_max * scrn->y_max))
	{
		if (scrn->iso[i].x < scrn->x_min)
			scrn->x_min = scrn->iso[i].x;
		if (scrn->iso[i].y < scrn->y_min)
			scrn->y_min = scrn->iso[i].y;
		i ++;
	}
}

void move(t_screen *scrn)
{
	int i;

	i = 0;
	while (i < (scrn->x_max * scrn->y_max))
	{
		scrn->iso[i].x += (0 - scrn->x_min);
		scrn->iso[i].y += (0 - scrn->y_min);
		if (scrn->iso[i].x > scrn->x_width)
			scrn->x_width = scrn->iso[i].x;
		if (scrn->iso[i].y > scrn->y_height)
			scrn->y_height = scrn->iso[i].y;
		i ++;
	}
}

void scale(t_screen *scrn)
{
	int 	i;
	float 	a; 
	float 	b;

	if (scrn->y_height >= HEIGHT)
		a = scrn->y_height - 1 / HEIGHT;
	else
		a = HEIGHT / scrn->y_height -1;
	if (scrn->x_width-1 >= WIDTH)
		b = scrn->x_width-1 / WIDTH;
	else
		b = WIDTH / scrn->x_width-1;
	if (a >= b)
		scrn->scale = b;
	else
		scrn->scale = a;
	i = 0;
	while (i < (scrn->y_max * scrn->x_max))
	{
		scrn->iso[i].x *= scrn->scale;
		scrn->iso[i].y *= scrn->scale;
		i ++;
	}
}

void	fdf_init (t_screen *scrn)
{
	calc_screen_cords(scrn);
	find_screen_limits(scrn);
	move(scrn);
	scale(scrn);
}