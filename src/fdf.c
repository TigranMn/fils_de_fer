/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:06:33 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/06/03 22:43:31 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_img(t_fdf *fdf)
{
	fdf->data.img =  mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->data.addr = mlx_get_data_addr(fdf->data.img, &(fdf->data.bits_per_pixel), &(fdf->data.line_length), &(fdf->data.endian));
}

void	init_view(t_fdf *fdf)
{
	fdf->view.zoom = 20;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_data	img;
	t_view	view;


	view.zoom = 20;
	if (argc != 2)
		return (1);
	read_file(argv[1], &fdf);
	fdf.mlx = mlx_init();
	fdf.mlx_win = mlx_new_window(fdf.mlx, 1920, 1080, "Kekw");
	init_view(&fdf);
	init_img(&fdf);
	draw(&fdf);
	mlx_loop(fdf.mlx);
}
