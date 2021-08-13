/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adjust_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 19:19:59 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 19:43:42 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

void	toogle(int *value)
{
	if (!(*value))
		*value = 1;
	else
		*value = 0;
}

void	adjust_zoom(t_fdf *fdf)
{
	if (fdf->moove.zoom)
		fdf->zoom += 1;
	else if (fdf->moove.dezoom)
		fdf->zoom -= 1;
	if (fdf->zoom < 1)
		fdf->zoom = 1;
}

void	adjust_shift(t_fdf *fdf)
{
	if (fdf->moove.add_shiftx)
		fdf->shift_x += 10;
	else if (fdf->moove.less_shiftx)
		fdf->shift_x -= 10;
	if (fdf->moove.add_shifty)
		fdf->shift_y += 10;
	else if (fdf->moove.less_shifty)
		fdf->shift_y -= 10;
}

void	adjust_zdepth(t_fdf *fdf)
{
	if (fdf->moove.add_z_depth)
		fdf->z_depth += 1;
	else if (fdf->moove.less_z_depth)
		fdf->z_depth -= 1;
}

void	adjust_values(t_fdf *fdf)
{
	adjust_zoom(fdf);
	adjust_shift(fdf);
	adjust_zdepth(fdf);
}
