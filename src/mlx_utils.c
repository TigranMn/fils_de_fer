/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:31:00 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/06/04 16:30:54 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

// void	get_zoomed(float *x, float*y, *float toX, float *toY)

void	isometric(float *x, float *y, int z)
{
	float	prevX;
	float	prevY;
	
	prevX = *x;
	prevY = *y;
	
 	*x = (prevX - prevY) * cos(0.5);
	*y = (prevX + prevY) * sin(0.5) - z;
}

void	draw_algo(float x, float y, float toX, float toY, t_fdf* fdf)
{
	float	x_step;
	float	y_step;
	float	max;
	int		z;
	int		toZ;
	int		color;

	z = fdf->map[(int)y][(int)x];
	toZ = fdf->map[(int)(toY)][(int)(toX)];
	if (z || toZ)
		color = 0xff00000;
	else 
		color = 0xffffff;
	x *= fdf->view.zoom;
	y *= fdf->view.zoom;
	toX *= fdf->view.zoom;
	toY *= fdf->view.zoom;
	x_step = toX - x;
	y_step = toY - y;
	isometric(&x, &y, z);
	isometric(&toX, &toY, toZ);
	if (x_step > y_step)
		max = x_step;
	else
		max = y_step;
	if (max < 0)
		max *= -1;

	x_step /= max;
	y_step /= max;

	while ((int)(x - toX) || (int)(y - toY))
	{
		ft_mlx_pixel_put(&fdf->data, x, y, color);
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