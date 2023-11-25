#include "fdf.h"

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

/* Parse through the first line and store width of map*/
static void check_first_line (int fd, t_screen *map)
{
	char	**arr;
	char 	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		ft_errexit("Map is empty.");
	}
	arr = ft_split(line, ' ');
	while (arr[(*map).x_max])
		(*map).x_max ++;
	free_arr (arr, (*map).x_max);
}

/* Parse through the rest of the map store height of map */
int	check_for_shape(int fd, t_screen *map, char *str)
{
	char	*line;
	char	**arr;
	int 	cols;

	check_first_line(fd, map);
	fd = open (str, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		arr = ft_split(line, ' ');
		cols = 0;
		while (arr[cols])
			cols ++;
		if (cols < (*map).x_max || cols > (*map).x_max)
		{
			free_arr (arr, cols);
			free(line);
			close (fd);
			return (-1);
		}
		else
			free_arr (arr, cols);
		free(line);
		(*map).y_max ++;
	}
	ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
	close(fd);
	return (1);
}