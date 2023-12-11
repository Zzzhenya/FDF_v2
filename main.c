#include "fdf.h"

t_screen *init_screen(t_screen	*scrn)
{
	scrn = malloc (sizeof (t_screen));
	if (!scrn)
		return (0);
	scrn->a = 360;//35.264 * M_PI/180;
	scrn->b = 35.264 * M_PI/180;
	scrn->x_max = 0;
	scrn->y_max = 0;
	scrn->z_max = 0;
	scrn->z_min = 0;
	scrn->scale = 20;
	scrn->iso = NULL;
	scrn->cord = NULL;
	return (scrn);
}

int main(int argc, char **argv)
{
	t_screen	*scrn;

	scrn = NULL;
	if (argc != 2)
	{
		ft_printf ("	Usage: ./fdf *.fdf\n");
		return (EXIT_FAILURE);
	}
	ft_printf ("file: %s\n", argv[1]);
	scrn = init_screen (scrn);
	if (!scrn)
		ft_errexit("t_screen init error");
	parse_and_store (scrn, argv[1]);
	fdf_init (scrn);
	launch_mlx_window(scrn);
	free_coord(scrn->cord);
	free_vert(scrn->iso);
	free_screen (scrn);
	return (EXIT_SUCCESS);
}