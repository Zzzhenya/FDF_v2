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
	float	x;
	float	y;
	float	z;

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
	float	x;
	float	y;
	float	z;

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
	float	x;
	float	y;
	float	z;

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
