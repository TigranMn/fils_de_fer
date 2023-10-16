/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:31:00 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/16 20:13:45 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (data->addr && x < 1920 && y < 1080 && x > 0 && y > 0)
	{
		dst = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

// void	get_zoomed(float *x, float*y, *float toX, float *toY)

void	isometric(float *x, float *y, int z)
{
	float	prev_x;
	float	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.5);
	*y = (prev_x + prev_y) * sin(0.5) - z;
}

void	final_draw(t_fdf *fdf, float x, float y, int z)
{
	ft_mlx_pixel_put(
		&fdf->data,
		(x + 960 - (sqrt((pow(fdf->width, 2) + pow(fdf->height, 2))) / 2)
			* fdf->view.zoom / 4),
		(y + 540 - (sqrt((pow(fdf->width, 2) + pow(fdf->height, 2))) / 2)
			* fdf->view.zoom / 2), get_color(z));
}

void	draw_algo(t_points points, float toX, float toY, t_fdf *fdf)
{
	float	x_step;
	float	y_step;
	float	max;
	int		z;
	int		to_z;

	z = fdf->map[(int)points.x][(int)points.y];
	to_z = fdf->map[(int)(toY)][(int)(toX)];
	zoom(&points, fdf, &toX, &toY);
	isometric(&points.y, &points.x, z);
	isometric(&toX, &toY, to_z);
	x_step = toX - points.y;
	y_step = toY - points.x;
	if (fabsf(x_step) > fabsf(y_step))
		max = fabsf(x_step);
	else
		max = fabsf(y_step);
	x_step /= max;
	y_step /= max;
	while ((int)(points.y - toX) || (int)(points.x - toY))
	{
		final_draw(fdf, points.y, points.x, z);
		points.y += x_step;
		points.x += y_step;
	}
}

void	draw(t_fdf *fdf)
{
	t_points	points;

	points.x = 0;
	while (points.x < fdf->height)
	{
		points.y = 0;
		while (points.y < fdf->width)
		{
			if (points.x < fdf->height - 1)
				draw_algo(points, points.y, points.x + 1, fdf);
			if (points.y < fdf->width - 1)
				draw_algo(points, points.y + 1, points.x, fdf);
		points.y++;
		}
		points.x++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->data.img, 0, 0);
}
