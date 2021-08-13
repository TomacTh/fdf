/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 19:09:20 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 12:18:22 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_file(char *filename)
{
	int	fd;

	if (open(filename, O_DIRECTORY) != -1)
	{
		close(fd);
		ft_putstr_fd("Arg must be a map file not a directory\n", 2);
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("fd error: ");
		exit(1);
	}
	return (fd);
}

int	check_arg(int ac, char *filename)
{
	size_t	len;

	if (ac != 2)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(1);
	}
	len = ft_strlen(filename);
	if (len > 4)
	{
		if (!ft_strcmp(&filename[len - 4], ".fdf"))
			return (0);
	}
	ft_putstr_fd("Argument must be a file in format: *.fdf\n", 2);
	exit(1);
}

unsigned int	tab_len(void **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		++i;
	return (i);
}

void	ft_free_map(t_fdf *fdf, unsigned int len)
{
	if (fdf->map)
	{
		while (len < fdf->height)
		{
			free(fdf->map[len]);
			++len;
		}
		free(fdf->map);
		fdf->map = 0;
	}
}

int	recursive_error(char *str, char **strs, unsigned int len, t_fdf *fdf)
{
	if (fdf->fd)
	{
		close(fdf->fd);
		fdf->fd = 0;
	}
	if (!fdf->error_code)
		fdf->error_code = 1;
	if (str)
		free(str);
	free_split(strs, -1);
	ft_free_map(fdf, len);
	return (-1);
}

char	*ft_str_tolower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] += 32;
	}
	return (str);
}

void	quit(t_fdf *fdf, char *err)
{
	t_mlx	*mlx;

	mlx = fdf->mlx;
	ft_free_map(fdf, 0);
	if (err)
	{
		ft_putstr_fd(err, 2);
		exit(1);
	}
	if (mlx->img)
		mlx_destroy_image(mlx->ptr, mlx->img->img);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->ptr, mlx->win_ptr);
	if (mlx->ptr)
		free((void *)mlx->ptr);
	exit(0);
}

float	get_abs(float i)
{
	if (i < 0)
		return (-i);
	return (i);
}

float	get_fmax(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float	get_fmin(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	get_imax(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	get_imin(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	iso(float *x, float *y, float z, float z_value)
{
	float	tempx;
	float	tempy;

	tempx = *x;
	tempy = *y;
	*x = (*x - *y);
	*y = ((tempx + tempy) / 2) - (z * z_value);
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
	iso(&coord.x, &coord.y, origin.z, fdf->z_value);
	iso(&coord.x1, &coord.y1, end.z, fdf->z_value);
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

void	new_image(t_fdf *fdf, t_mlx *mlx, t_img *img)
{
	img->img = mlx_new_image(mlx->ptr, 1920, 1080);
	if (!img->img)
		quit(fdf, "Cannot create mlx image\n");
	img->addr = (int *)mlx_get_data_addr(img->img, &(img->bpp),
			&(img->line), &(img->endian));
	img->w = 1920;
	img->h = 1080;
}

int	key_press(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		quit(fdf, 0);
	return (0);
}

int	key_release(int keycode)
{
	printf("release: %i\n", keycode);
	return (0);
}

void	set_zoom_shift_and_z(t_fdf *fdf)
{
	float	zoomy;
	float	zoomx;

	zoomx = 1920 / (fdf->width - 1);
	zoomy = 1080 / (fdf->height - 1);
	fdf->zoom = get_fmin(zoomx, zoomy) / ((get_fmax(fdf->width, fdf->height)
				/ get_fmin(fdf->width, fdf->height)) * 2);
	if (fdf->zoom < 0)
		fdf->zoom = 0;
	fdf->shift_x = (1920 - (fdf->zoom * (fdf->width - 1))) / 2 ;
	fdf->shift_y = (1080 - (fdf->zoom * (fdf->height - 1))) / 2 ;
	fdf->z_value = 2;
}

void	init_mlx(t_mlx *mlx, t_fdf *fdf)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		quit(fdf, "Cannot init mlx\n");
	mlx->win_ptr = mlx_new_window(mlx->ptr, 1920, 1080, "fdf");
	if (!mlx->win_ptr)
		quit(fdf, "Cannot create window\n");
	new_image(fdf, mlx, mlx->img);
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
	mlx_hook(mlx.win_ptr, 3, (1L << 1), &key_release, &fdf);
	mlx_loop(mlx.ptr);
	return (0);
}
