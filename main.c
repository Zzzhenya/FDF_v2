#include "fdf.h"

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