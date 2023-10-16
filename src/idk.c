/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:30 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/16 20:14:17 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	zoom(t_points *points, t_fdf *fdf, float *toX, float *toY)
{
	points->x *= fdf->view.zoom;
	points->y *= fdf->view.zoom;
	*toX *= fdf->view.zoom;
	*toY *= fdf->view.zoom;
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
