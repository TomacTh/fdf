/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 19:09:20 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/12 16:50:23 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_file(char *filename)
{
	int fd;

	if(open(filename, O_DIRECTORY) != -1)
	{
		ft_putstr_fd("Arg must be a map file not a directory\n", 2);
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		perror("fd error: ");
		exit(1);
	}
	return (fd);
}

int	check_arg(int ac, char *filename)
{
	size_t	len;

	if(ac != 2)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(1);
	}
	len = ft_strlen(filename);
	if(len > 4)
	{
		if	(!ft_strcmp(&filename[len - 4], ".fdf"))
			return (0);
	}
	ft_putstr_fd("Argument must be a file in format: *.fdf\n", 2);
	exit(1);
}

unsigned int	tab_len(void **tab)
{
	unsigned int i;

	i = 0;
	while(tab[i])
		++i;
	return (i);
}

void	ft_free_map(t_fdf *fdf, unsigned int len)
{
	if (fdf->map)
	{
		while(len < fdf->height)
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
	if(fdf->fd)
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
	while(str[++i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] += 32;
	}
	return (str);
}


void	quit(t_fdf *fdf, char *err)
{	
	t_mlx *mlx;

	mlx = fdf->mlx;
	ft_free_map(fdf, 0);
	if(err)
	{
		ft_putstr_fd(err, 2);
		exit(1);
	}
	if (mlx->img)
		mlx_destroy_image(mlx->ptr, mlx->img->img);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->ptr, mlx->win_ptr);
	if (mlx->ptr)
		free((void*)mlx->ptr);
	exit(0);
}

float	get_abs(float i)
{
	if(i < 0)
		return (-i);
	return (i);
}

float	get_max(float a, float b)
{
	if(a > b)
		return (a);
	else
		return (b);
}

void	iso(float *x, float *y, float z)
{
	//float u;
	//float v;

	//*x = (*x-z)/sqrt(2);
	//*y = (*x+2*(*y)+z)/sqrt(6);

	//*x = u;
	//*y = v;
	float tempx = *x;
	float tempy = *y;
	//*x = (*x + z)/ sqrt(2);
	//*y = (temp + 2* (*y) - z) / sqrt(6);
	//*x = (*x - *y) * cos(0.82);
	//*y = (*x + *y) * sin(0.82) - z;

	*x =  (*x - *y);
	*y = ((tempx + tempy) / 2) - z;

	//printf("x: %i oldx: %i\n", (int)get_abs(*x), (int)et_abs(tempx));
	//printf("y: %i oldy: %i\n", (int)get_abs(*y), (int)get_abs(tempy));

	//*y -=   z;
}


void	calc_step_and_max(float *x_step, float *y_step, int *max, t_coordinates coord)
{
	*x_step = (coord.x1 - coord.x);
	*y_step = (coord.y1 - coord.y);
	*max = get_max(get_abs(*x_step), get_abs(*y_step));
	*x_step /= *max;
	*y_step /= *max;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int		*dst;

	if((x >= 0 && y >= 0) && (x < img->w &&  y < img->h))
	{
		dst = img->addr + (y * img->w + x);
		*(unsigned int *)dst = color;
	}
}

void	bresenham_algo(t_coordinates coord, t_fdf *fdf)
{
	t_point origin;
	t_point	end;
	float x_step;
	float y_step;
	int max;

	origin = fdf->map[(int)coord.y][(int)coord.x];
	end = fdf->map[(int)coord.y1][(int)coord.x1];
	int zoomy;
	int zoomx;
	int zoom;

	zoomx = 1920 / (fdf->width - 1);
	zoomy = 1080 / (fdf->height - 1);
	zoom = (int)fmin(zoomx, zoomy) / ((fmax(fdf->width, fdf->height) / fmin(fdf->width, fdf->height)) * 2);
	//ZOOM//
	coord.x *= zoom;
	coord.y *= zoom;
	coord.x1 *= zoom;
	coord.y1 *= zoom;
	//ZOOM//

/* 	x_step = (coord.x1 - coord.x);
	y_step = (coord.y1 - coord.y);
	max = get_max(get_abs(x_step), get_abs(y_step));
	x_step /= max;
	y_step /= max; */

	iso(&coord.x, &coord.y, origin.z);
	iso(&coord.x1, &coord.y1, end.z);

	int shiftx = (1920 - (zoom * (fdf->width - 1))) / 2 ;
	int shifty = (1080 - (zoom * (fdf->height - 1))) / 2 ;
	//SHIFT//
	coord.x += shiftx;
	coord.y += shifty;
	coord.x1 += shiftx;
	coord.y1 += shifty;
	//SHIFT//
	calc_step_and_max(&x_step, &y_step, &max, coord);

	while((int)(coord.x - coord.x1) || (int)(coord.y - coord.y1))
	{
		my_mlx_pixel_put(fdf->mlx->img, coord.x, coord.y, origin.color);
		coord.x += x_step;
		coord.y += y_step;
	}
}

int	main_loop(t_fdf *fdf)
{
	unsigned int y;
	unsigned int x;
	t_mlx		*mlx;

	y = 0;
	mlx = fdf->mlx;
	
	
	while(y < fdf->height)
	{
		x = 0;
		while(x < fdf->width)
		{
			if(x < fdf->width -1)
			bresenham_algo((t_coordinates){x, y, x + 1, y}, fdf);
			if(y < fdf->height - 1)
			bresenham_algo((t_coordinates){x, y, x, y + 1}, fdf);
			++x;
		}
		++y;
	}
	
	
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, fdf->mlx->img->img, 0, 0);
	return (0);
}


//0->0
//|
//0
void	new_image(t_fdf *fdf, t_mlx *mlx, t_img *img)
{
	img->img = mlx_new_image(mlx->ptr, 1920, 1080);
	if (!img->img)
		quit(fdf, "Cannot create mlx image\n");
	img->addr = (int *)mlx_get_data_addr(img->img, &(img->bpp),
			&(img->line), &(img->endian));
	img->w = 1920;
	img->h = 1080;
	//mlx->img = &img;
}


int		key_press(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		quit(fdf, 0);
	return (0);
}

int		key_release(int keycode)
{
	printf("release: %i\n", keycode);
	return (0);
}

int main(int ac, char **av)
{
	t_fdf fdf;
	t_mlx mlx;
	t_img img;

	check_arg(ac, av[1]);
	ft_bzero(&fdf, sizeof(t_fdf));
	ft_bzero(&mlx, sizeof(t_mlx));
	fdf.mlx = &mlx;
	fdf.fd = check_file(av[1]);
	if(recursive_parse(&fdf, 0) == -1)
		quit(&fdf, "Parse error\n");
	close(fdf.fd);
	mlx.ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.ptr, 1920, 1080, "fdf");
	mlx.img = &img;
	new_image(&fdf, &mlx, mlx.img);
	mlx_loop_hook(mlx.ptr, &main_loop, &fdf);
	mlx_hook(mlx.win_ptr, 2, (1L << 0), &key_press, &fdf);
	mlx_hook(mlx.win_ptr, 3, (1L << 1), &key_release, &fdf);
	//mlx_hook(game.info.win, 2, (1L << 0), &key_press, &game);
	//mlx_hook(game.info.win, 3, (1L << 1), &key_release, &game);
	//mlx_hook(game.info.win, 33, (1L << 17), quit, &game);
/* 	int y = -1;
	int x;
	while(++y < 1080)
	{
		x = -1;
		while(++x < 1920)
			my_mlx_pixel_put(fdf.mlx->img, x, y, 0xffffff);
	}

	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->img, 0, 0);
	ft_bzero(img.addr, (sizeof(unsigned int) * 1920 * 1080));
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->img, 0, 0); */
	mlx_loop(mlx.ptr);
	return (0);

}


/* int	quit(t_game *game)
{
	free(game->info.spritesdist);
	free(game->info.zbuf);
	free(game->sprites);
	free(game->str);
	clean_textures(game);
	if (game->map)
		free_map(game->map, game->rows);
	if (game->info.img.img)
		mlx_destroy_image(game->info.mlx, game->info.img.img);
	if (game->info.win)
		mlx_destroy_window(game->info.mlx, game->info.win);
	if (game->info.mlx)
	{
		mlx_destroy_display(game->info.mlx);
		free(game->info.mlx);
	}
	exit(0);
	return (0);
}

void	calc(t_game *game)
{
	int		x;
	t_cast	ray;
	t_info	*info;

	info = &game->info;
	x = -1;
	while (++x < game->w)
	{
		ft_bzero(&ray, sizeof(ray));
		ray.cameraX = 2 * x / (double)game->w - 1;
		ray.rx = info->dx + info->plane_x * ray.cameraX;
		ray.ry = info->dy + info->plane_y * ray.cameraX;
		ray.deltaX = fabs(1 / ray.rx);
		ray.deltaY = fabs(1 / ray.ry);
		ray.mapX = (int)info->px;
		ray.mapY = (int)info->py;
		calc_step_side(info, &ray);
		dda(game, &ray);
		dda2(game, &ray);
		choose_good_texture(game, &ray);
		draw_text(game, &ray, x);
		vertical_stripe(game, x, 0, ray.drawStart - 1);
		vertical_stripe(game, x, ray.drawEnd + 1, game->h - 1);
		info->zbuf[x] = ray.perpwall;
	}
}

int	main_loop(t_game *game)
{
	t_info	info;

	info = game->info;
	calc(game);
	sprite(game);
	if (!info.toogle_minimap)
		minimap(game);
	mlx_do_sync(info.mlx);
	if (game->bmp)
		return (bmp(game->info.img, game));
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	movement(game);
	return (0);
}

int	init(t_game *game)
{
	init_sprites(game);
	init_game(game);
	init_textures(game);
	game->info.zbuf = malloc(sizeof(double) * game->w);
	if (!game->info.zbuf)
		return (display_error(strerror(errno), game));
	game->info.spritesdist = malloc(sizeof(double) * game->count_sprites);
	if (!game->info.spritesdist)
		return (display_error(strerror(errno), game));
	new_image(game, &game->info.img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	check_arg(argc, argv, &game);
	parsing(argv[1], &game);
	init(&game);
	if (game.bmp)
		return (main_loop(&game));
	if ((game.rows * 6 >= game.h || game.maxline * 6 >= game.w))
	{
		game.minimap = 1;
		game.info.toogle_minimap = 1;
	}
	game.info.win = mlx_new_window(game.info.mlx, game.w, game.h, "cub3D");
	mlx_loop_hook(game.info.mlx, &main_loop, &game);
	mlx_hook(game.info.win, 2, (1L << 0), &key_press, &game);
	mlx_hook(game.info.win, 3, (1L << 1), &key_release, &game);
	mlx_hook(game.info.win, 33, (1L << 17), quit, &game);
	mlx_loop(game.info.mlx);
	return (0);
} */
