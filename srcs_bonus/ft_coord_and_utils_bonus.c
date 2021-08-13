/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coord_and_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 17:44:09 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 19:23:08 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

void	projection_bonus(float *x, float *y, int z_tab[2], int projection)
{
	float	tempx;

	tempx = *x;
	if (!projection)
	{
		*x = (*x - *y);
		*y = ((tempx + *y) / 2) - (z_tab[0] * z_tab[1]);
	}
	else
		*y -= (z_tab[0] * z_tab[1]);
}

void	calc_step_and_max(float *x_step, float *y_step,
		int *max, t_coordinates coord)
{
	*x_step = (coord.x1 - coord.x);
	*y_step = (coord.y1 - coord.y);
	*max = get_imax(get_abs(*x_step), get_abs(*y_step));
	*x_step /= *max;
	*y_step /= *max;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int		*dst;
	int		positive_pixel;
	int		in_screen_pixel;

	positive_pixel = (x >= 0 && y >= 0);
	in_screen_pixel = (x < img->w && y < img->h);
	if (positive_pixel && in_screen_pixel)
	{
		dst = img->addr + (y * img->w + x);
		*(unsigned int *)dst = color;
	}
}

void	zoom_coord(t_coordinates *coord, float zoom)
{
	coord->x *= zoom;
	coord->y *= zoom;
	coord->x1 *= zoom;
	coord->y1 *= zoom;
}

void	shift_coord(t_coordinates *coord, int shift_x, int shift_y)
{
	coord->x += shift_x;
	coord->x1 += shift_x;
	coord->y += shift_y;
	coord->y1 += shift_y;
}
