/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:31:00 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/16 20:00:35 by tmnatsak         ###   ########.fr       */
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

int	get_color(int z)
{
	if (abs(z) > 300)
		return (0x92f5c0);
	if (abs(z) > 200)
		return (0x9c42f5);
	if (abs(z) > 80)
		return (0x4287f5);
	if (abs(z) > 20)
		return (0xff0000);
	if (abs(z) > 0)
		return (0x42f587);
	return (0xffffff);
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

void	draw_algo(float x, float y, float toX, float toY, t_fdf *fdf)
{
	float	x_step;
	float	y_step;
	float	max;
	int		z;
	int		to_z;

	z = fdf->map[(int)y][(int)x];
	to_z = fdf->map[(int)(toY)][(int)(toX)];
	x *= fdf->view.zoom;
	y *= fdf->view.zoom;
	toX *= fdf->view.zoom;
	toY *= fdf->view.zoom;
	isometric(&x, &y, z);
	isometric(&toX, &toY, to_z);
	x_step = toX - x;
	y_step = toY - y;
	if (fabsf(x_step) > fabsf(y_step))
		max = fabsf(x_step);
	else
		max = fabsf(y_step);
	x_step /= max;
	y_step /= max;
	while ((int)(x - toX) || (int)(y - toY))
	{
		final_draw(fdf, x, y, z);
		x += x_step;
		y += y_step;
	}
}

void	draw(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (i < fdf->height - 1)
				draw_algo(j, i, j, i + 1, fdf);
			if (j < fdf->width - 1)
				draw_algo(j, i, j + 1, i, fdf);
		j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->data.img, 0, 0);
}
