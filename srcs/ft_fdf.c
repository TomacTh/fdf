/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:21:25 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 16:23:29 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	bresenham_algo(t_coordinates coord, t_fdf *fdf)
{
	t_point	origin;
	t_point	end;
	float	x_step;
	float	y_step;
	int		max;

	origin = fdf->map[(int)coord.y][(int)coord.x];
	end = fdf->map[(int)coord.y1][(int)coord.x1];
	zoom_coord(&coord, fdf->zoom);
	iso(&coord.x, &coord.y, origin.z, fdf->z_depth);
	iso(&coord.x1, &coord.y1, end.z, fdf->z_depth);
	shift_coord(&coord, fdf->shift_x, fdf->shift_y);
	calc_step_and_max(&x_step, &y_step, &max, coord);
	while ((int)(coord.x - coord.x1) || (int)(coord.y - coord.y1))
	{
		my_mlx_pixel_put(fdf->mlx->img, coord.x, coord.y, origin.color);
		coord.x += x_step;
		coord.y += y_step;
	}
}

int	main_loop(t_fdf *fdf)
{
	unsigned int	y;
	unsigned int	x;
	t_mlx			*mlx;

	y = 0;
	mlx = fdf->mlx;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			if (x < fdf->width - 1)
				bresenham_algo((t_coordinates){x, y, x + 1, y}, fdf);
			if (y < fdf->height - 1)
				bresenham_algo((t_coordinates){x, y, x, y + 1}, fdf);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, fdf->mlx->img->img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		quit(fdf, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;
	t_mlx	mlx;
	t_img	img;

	check_arg(ac, av[1]);
	ft_bzero(&fdf, sizeof(t_fdf));
	ft_bzero(&mlx, sizeof(t_mlx));
	fdf.mlx = &mlx;
	fdf.fd = check_file(av[1]);
	if (recursive_parse(&fdf, 0) == -1)
		quit(&fdf, "Parse error\n");
	close(fdf.fd);
	set_zoom_shift_and_z(&fdf);
	mlx.img = &img;
	init_mlx(&mlx, &fdf);
	mlx_loop_hook(mlx.ptr, &main_loop, &fdf);
	mlx_hook(mlx.win_ptr, 2, (1L << 0), &key_press, &fdf);
	mlx_loop(mlx.ptr);
	return (0);
}
