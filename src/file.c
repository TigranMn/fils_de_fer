/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:00:53 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/07 20:55:19 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	fill_map(int **map, t_fdf *fdf, int fd)
{
	int		i;
	int		j;
	char	**splitted;
	char	*line;

	i = 0;
	while (i < (*fdf).height)
	{
		j = 0;
		line = get_next_line(fd);
		map[i] = malloc(sizeof(int) * fdf->width);
		if (!map[i])
			exit(1);
		splitted = ft_split(line, ' ');
		while (splitted[j])
		{
			map[i][j] = ft_atoi(splitted[j]);
			j++;
		}
		free(line);
		free_2d_str_arr(splitted, j);
		i++;
	}
}

int	**get_map(char *file, t_fdf *fdf)
{
	int		fd;
	int		**map;

	map = malloc(sizeof(int *) * fdf->height);
	if (!map)
		exit(1);
	fd = open(file, O_RDONLY);
	fill_map(map, fdf, fd);
	return (map);
}

int	get_width(char *line)
{
	char	**splitted;
	char	*trimmed;
	int		i;

	i = 0;
	trimmed = ft_strtrim(line, "\n");
	splitted = ft_split(trimmed, ' ');
	while (splitted[i] != '\0')
		i++;
	free_2d_str_arr(splitted, i);
	free(trimmed);
	return (i);
}

void	get_wh(char *file, t_fdf *fdf)
{
	int		height;
	char	*line;
	int		fd;
	int		line_width;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	height = 0;
	line = get_next_line(fd);
	line_width = get_width(line);
	while (line)
	{
		height++;
		if (line_width != get_width(line))
			ft_error("Invalid map");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fdf->width = line_width;
	fdf->height = height;
}

void	read_file(char *file, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	get_wh(file, fdf);
	fdf->map = get_map(file, fdf);
}
