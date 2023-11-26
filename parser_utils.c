#include "fdf.h"
#include <stdio.h>

/* File type check */
int	ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;	

	i = 0;
	j = 0;
	while (haystack[i] != '\0' && needle[j] != '\0')
	{
		if (haystack[i] == needle[j])
			j ++;
		i ++;
	}
	if (j == ft_strlen(needle))
		return (1);
	else
		return (0);
}

/* Parse through the first line and store width of map
static void check_first_line (int fd, t_screen *map)
{
	char	*arr;
	char 	**line;
	int i;

	i = 0;
	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		return;
		//ft_errexit("Map is empty.");
	}
	ft_printf("first line:%s\n", line);
	arr = ft_split(line, ' ');
	while (arr[i] != NULL)
	{
		ft_printf("One\n");
		i ++;
	}
	map->x_max = i;
	free_arr (&arr, (*map).x_max);
	free (line);
	close(fd);
}
*/
/* Parse through the rest of the map store height of map */
void	check_for_shape(int fd, t_screen *map)
{
	char	*line;
	char	**arr;
	int 	cols;
	int		err;


	err = 0;
	ft_printf("check_for_shape\n");
	line = get_next_line(fd);
	while (line)
	{
		arr = ft_split(line, ' ');
		free (line);
		cols = 0;
		while (arr[cols])
			cols ++;
		free_arr (arr);
		if (cols < (*map).x_max || cols > (*map).x_max)
			err = 1;
		line = get_next_line(fd);
	}
	if (err > 0)
	{
		close(fd);
		free (map);
		ft_errexit("Map is not a rectangle.");
	}
}

void print_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%d :%s\n",i, arr[i]);
		i ++;
	}

}

void get_map_dims(int fd, t_screen *scrn, int i)
{
	char	*line;
	char	**arr;

	ft_printf("check_for_dims:");
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		free (scrn);
		ft_errexit("Empty map");
	}
	arr = ft_split(line, ' ');
	while (arr[i])
		i ++;
	scrn->x_max = i;
	free_arr(arr);
	i = 0;
	while (line)
	{
		free (line);
		i ++;
		line = get_next_line(fd);
	}
	scrn->y_max = i;
	ft_printf("x,y max %d, %d\n", scrn->x_max, scrn->y_max);
}