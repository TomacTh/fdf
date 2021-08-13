/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 15:33:10 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 19:26:06 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

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
	while ((int)(coord.x - coord.x1) || (int)(coord.y - coord.y1))
	{
		my_mlx_pixel_put(fdf->mlx->img, coord.x, coord.y, origin.color);
		coord.x += x_step;
		coord.y += y_step;
	}
}

int	main_loop_bonus(t_fdf *fdf)
{
	unsigned int	y;
	unsigned int	x;
	t_mlx			*mlx;

	y = 0;
	mlx = fdf->mlx;
	adjust_values(fdf);
	ft_bzero(fdf->mlx->img->addr, sizeof(unsigned int) * 1080 * 1920);
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			if (x < fdf->width - 1)
				bresenham_algo_bonus((t_coordinates){x, y, x + 1, y}, fdf);
			if (y < fdf->height - 1)
				bresenham_algo_bonus((t_coordinates){x, y, x, y + 1}, fdf);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, fdf->mlx->img->img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_fdf *fdf)
{
	t_moove	*moove;

	moove = &fdf->moove;
	if (keycode == ESC_KEY)
		quit(fdf, 0);
	else if (keycode == PROJECTION)
		toogle(&fdf->projection);
	else if (keycode == ZOOM || keycode == DEZOOM)
		zoom_or_dezoom_key(keycode, moove);
	else if (keycode >= SHIFT_LEFT && keycode <= SHIFT_UP)
		shift_keys(keycode, moove);
	else if (keycode == Z_DEPTH_LESS || keycode == Z_DEPTH_MORE)
		z_depth_keys(keycode, moove);
	return (0);
}

int	key_release(int keycode, t_fdf *fdf)
{
	t_moove	*moove;

	moove = &fdf->moove;
	ft_bzero(moove, sizeof(t_moove));
	if (keycode == ESC_KEY)
		quit(fdf, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;
	t_mlx	mlx;
	t_img	img;
	t_moove	moove;

	check_arg(ac, av[1]);
	ft_bzero(&fdf, sizeof(t_fdf));
	ft_bzero(&mlx, sizeof(t_mlx));
	fdf.mlx = &mlx;
	fdf.fd = check_file(av[1]);
	if (recursive_parse(&fdf, 0) == -1)
		quit(&fdf, "Parse error\n");
	close(fdf.fd);
	set_zoom_shift_and_z(&fdf);
	ft_bzero(&moove, sizeof(t_moove));
	fdf.moove = moove;
	mlx.img = &img;
	init_mlx(&mlx, &fdf);
	mlx_loop_hook(mlx.ptr, &main_loop_bonus, &fdf);
	mlx_hook(mlx.win_ptr, 2, (1L << 0), &key_press, &fdf);
	mlx_hook(mlx.win_ptr, 3, (1L << 1), &key_release, &fdf);
	mlx_loop(mlx.ptr);
	return (0);
}
