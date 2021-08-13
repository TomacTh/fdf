/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:18:51 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 16:11:55 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	check_file(char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd != -1)
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
	fdf->z_depth = 2;
}
