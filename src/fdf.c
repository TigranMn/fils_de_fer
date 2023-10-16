/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:06:33 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/07 22:34:17 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_img(t_fdf *fdf)
{
	fdf->data.img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->data.addr = mlx_get_data_addr
		(fdf->data.img,
			&(fdf->data.bits_per_pixel),
			&(fdf->data.line_length), &(fdf->data.endian));
}

void	init_view(t_fdf *fdf)
{
	int	height;
	int	width;

	height = fdf->width * sin(0.5) + fdf->height * cos(0.5);
	width = fdf->width * cos(0.5) + fdf->height * sin(0.5);
	if (height < width)
		fdf->view.zoom = 1200 / height;
	else
		fdf->view.zoom = 1000 / width;
}

void	graphic_events(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_win, 2, 0, key_press, fdf);
	mlx_hook(fdf->mlx_win, 17, 0, close_window, fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (1);
	read_file(argv[1], &fdf);
	fdf.mlx = mlx_init();
	fdf.mlx_win = mlx_new_window(fdf.mlx, 1920, 1080, "Fdf");
	init_view(&fdf);
	init_img(&fdf);
	draw(&fdf);
	graphic_events(&fdf);
	mlx_loop(fdf.mlx);
}
