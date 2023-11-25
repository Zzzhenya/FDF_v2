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
/* Parse through the rest of the map store height of map 
int	check_for_shape(int fd, t_screen *map, char *str)
{
	char	*line;
	char	**arr;
	int 	cols;
	int    i;


	ft_printf("check_for_shape: %s\n", str);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		arr = ft_split(line, ' ');
		cols = 0;
		while (arr[cols] != (void *)0)
		{
			cols ++;
			if (i == 0)
				map->x_max = cols;
		}
		if (cols < (*map).x_max || cols > (*map).x_max)
		{
			break;
		}
		free (line);
		free_arr (arr, cols);
		(*map).y_max ++;
	}
	ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
	
	close(fd);
	ft_printf("%s\n", str);
	return (1);
}*/

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

int	check_for_shape(int fd, t_screen *map, char *str)
{
	char	*line;
	char	**arr;
	int     col;
	int i;

	i = 0;
	ft_printf("check_for_shape: %s\n", str);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			map->y_max = i;
			close(fd);
			if (i == 0)
				return (-1);
			return (1);
		}
		arr = ft_split(line, ' ');
		print_arr(arr);
		col = 0;
		while (arr[col])
		{
			if (i == 0)
				map->x_max++;
			col ++;
		}
		if (col < map->x_max || col > map->x_max)
		{
			free_arr (arr);
			arr = NULL;
			free (line);
			line = NULL;
			close(fd);
			ft_errexit("Not a rectangle");
		}
		free (line);
		line = NULL;
		free_arr(arr);
		arr = NULL;
		i ++;
	}
}