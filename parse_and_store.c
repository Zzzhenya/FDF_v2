#include "fdf.h"

int	store_3d_cords(t_screen *map, int fd, int i)
{
	char	*line;
	char 	**arr;
	int		rows;
	int 	cols;

	rows = 0;
	(*map).cord = malloc ((*map).x_max * (*map).y_max * sizeof(t_cord));
	if (!(*map).cord)
		return (-1);
	while (rows < (*map).y_max)
	{
		line = get_next_line(fd);
		arr = ft_split(line, ' ');
		free (line);
		cols = 0;
		while (cols < (*map).x_max)	
		{
			(*map).cord[i].y = rows;
			(*map).cord[i].x = cols;
			(*map).cord[i].z = ft_atoi(arr[cols]);
			cols ++;
			i ++;
		}
		free_arr(arr);
		rows ++;
	}
	return (0);
}

int ft_parse (char *str, t_screen *scrn)
{
	int 	fd;

	if (!ft_strstr(str, ".fdf"))
		return (0);
		//ft_errexit("Incorrect file type. It should be a .fdf");
	fd = open (str, O_RDONLY);
	if (fd < 0)
		//ft_errexit("open() error.");
		return (0);
	get_map_dims(fd, scrn, 0);
	close (fd);
	fd = open (str, O_RDONLY);
	if (fd < 0)
		//ft_errexit("open() error.");
		return (0);
	check_for_shape(fd, scrn);
	// check for numeric values, NULL, INT MAX and INT MIN
	close (fd);
	/*ft_printf("%d\n", scrn->x_max);*/
	return (1);
}

int parse_and_store(t_screen *scrn, char *name)
{
	int	fd;

	if (!ft_parse(name, scrn))
	{
		free_screen(scrn);
		ft_errexit("Parsing error");
	}
	fd = open (name, O_RDONLY);
	if (fd < 0)
	{
		free_screen(scrn);
		ft_errexit("open() error.");
		//return (0);
	}
	store_3d_cords(scrn, fd, 0);
	//print_t_cord(scrn);
	close (fd);
	return (1);
}