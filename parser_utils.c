/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:26:21 by sde-silv          #+#    #+#             */
/*   Updated: 2023/12/21 01:37:47 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	close_free_exit(int fd, t_screen *scrn, char *str)
{
	close(fd);
	free_screen(scrn);
	ft_errexit(str);
}

/* Check whether the map is a rectangle */
void	check_for_shape(int fd, t_screen *scrn)
{
	char	*line;
	char	**arr;
	int		cols;
	int		err;

	err = 0;
	line = get_next_line(fd);
	while (line)
	{
		arr = ft_splitbyspace(line);
		free (line);
		cols = 0;
		while (arr[cols])
			cols ++;
		if (arr)
			free_arr (arr);
		if (cols < scrn->x_max || cols > scrn->x_max)
			err = 1;
		line = get_next_line(fd);
	}
	if (err > 0)
		close_free_exit(fd, scrn, "Map is not a rectangle.");
}

void	get_map_dims(int fd, t_screen *scrn, int i)
{
	char	*line;
	char	**arr;

	line = get_next_line(fd);
	if (!line)
		close_free_exit(fd, scrn, "Empty map");
	arr = ft_splitbyspace(line);
	while (arr[i])
		i ++;
	scrn->x_max = i;
	if (arr)
		free_arr (arr);
	i = 0;
	while (line)
	{
		free (line);
		i ++;
		line = get_next_line(fd);
	}
	scrn->y_max = i;
}
