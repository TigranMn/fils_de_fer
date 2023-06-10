/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:05:12 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/06/04 16:29:25 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "./get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>

typedef struct t_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct t_view {
	int	zoom;
}	t_view;

typedef struct t_fdf {
	int		height;
	int		width;
	int		**map;
	t_view	view;
	t_data	data;

	void	*mlx;
	void	*mlx_win;
}	t_fdf;

void	read_file(char *file, t_fdf *fdf);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	free_2d_str_arr(char **split, int i);
void	free_2d_int_arr(int **split, int i);
int		ft_atoi(char *str);
void	ft_error(char *err);
int		is_digit(char *str);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw(t_fdf *fdf);
void	draw_algo(float x, float y, float toX, float toY, t_fdf* fdf);


#endif