/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:11:13 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/11 18:11:29 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_stuff_and_exit(t_screen *scrn, int fd)
{
	free_screen(scrn);
	close (fd);
	ft_errexit("Malloc failed");
}

void	store_3d_cords(t_screen *scrn, int fd, int i, int rows)
{
	char	*line;
	char	**arr;
	int		cols;

	scrn->cord = malloc (scrn->x_max * scrn->y_max * sizeof(t_cord));
	if (!scrn->cord)
		free_stuff_and_exit(scrn, fd);
	while (rows < scrn->y_max)
	{
		line = get_next_line(fd);
		arr = ft_split(line, ' ');
		free (line);
		cols = 0;
		while (cols < scrn->x_max)
		{
			scrn->cord[i].y = rows;
			scrn->cord[i].x = cols;
			scrn->cord[i].z = ft_atoi(arr[cols]);
			cols ++;
			i ++;
		}
		free_arr(arr);
		rows ++;
	}
}

/* check for numeric values, NULL, INT MAX and 
INT MIN after checking for shape*/
int	ft_parse(char *str, t_screen *scrn)
{
	int	fd;

	if (!ft_strstr(str, ".fdf"))
		return (1);
	fd = open (str, O_RDONLY);
	if (fd < 0)
		return (2);
	get_map_dims(fd, scrn, 0);
	close (fd);
	fd = open (str, O_RDONLY);
	if (fd < 0)
		return (2);
	check_for_shape(fd, scrn);
	close (fd);
	return (0);
}

int	parse_and_store(t_screen *scrn, char *name)
{
	int	fd;
	int	ret;

	ret = ft_parse(name, scrn); 
	if (ret > 0)
	{
		free_screen(scrn);
		if (ret == 1)
			ft_errexit("Incorrect file type. It should be a .fdf");
		else if (ret == 2)
			ft_errexit("open() error.");
		else
			ft_errexit("Parsing error");
	}
	fd = open (name, O_RDONLY);
	if (fd < 0)
	{
		free_screen(scrn);
		ft_errexit("open() error.");
	}
	store_3d_cords(scrn, fd, 0, 0);
	close (fd);
	return (1);
}
