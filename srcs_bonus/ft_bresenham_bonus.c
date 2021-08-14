/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:27:03 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/14 17:29:23 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

int	color_interpolation(int color_a, int color_b, int max, int i)
{
	t_rgb	a;
	t_rgb	b;
	t_rgb	c;
	int		color;
	float	t;

	if (!i)
		return (color_b);
	ft_bzero(&a, sizeof(a));
	ft_bzero(&b, sizeof(b));
	ft_bzero(&c, sizeof(c));
	color = 0;
	t = (i / (float)(max));
	a.r = (color_a >> 16);
	a.g = (color_a >> 8);
	a.b = (color_a);
	b.r = (color_b >> 16);
	b.g = (color_b >> 8);
	b.b = (color_b);
	c.r = a.r + (a.r - b.r) * t;
	c.g = a.g + (a.g - b.g) * t;
	c.b = a.b + (a.b - b.b) * t;
	color = ((c.r << 16) | (c.g << 8) | c.b);
	return (color);
}

void	loop_bresenham(t_coordinates coord,
	float steps [2], int colors_and_max[3], t_fdf *fdf)
{
	int	color;
	int	i;
	int	max;

	i = 0;
	max = colors_and_max[2];
	color = colors_and_max[0];
	while ((int)(coord.x - coord.x1) || (int)(coord.y - coord.y1))
	{
		if (colors_and_max[0] != colors_and_max[1])
			color = color_interpolation(colors_and_max[1],
					colors_and_max[0], max, i);
		my_mlx_pixel_put(fdf->mlx->img, coord.x, coord.y, color);
		coord.x += steps[0];
		coord.y += steps[1];
		++i;
	}
}

void	bresenham_algo_bonus(t_coordinates coord, t_fdf *fdf)
{
	t_point	origin;
	t_point	end;
	float	x_step;
	float	y_step;
	int		max;

	origin = fdf->map[(int)coord.y][(int)coord.x];
	end = fdf->map[(int)coord.y1][(int)coord.x1];
	zoom_coord(&coord, fdf->zoom);
	projection_bonus(&coord.x, &coord.y,
		(int [2]){origin.z, fdf->z_depth}, fdf->projection);
	projection_bonus(&coord.x1, &coord.y1,
		(int [2]){end.z, fdf->z_depth}, fdf->projection);
	shift_coord(&coord, fdf->shift_x, fdf->shift_y);
	calc_step_and_max(&x_step, &y_step, &max, coord);
	loop_bresenham(coord, (float [2]){x_step, y_step},
		(int [3]){origin.color, end.color, max}, fdf);
}
