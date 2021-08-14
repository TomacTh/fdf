/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 17:46:27 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/14 17:29:14 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

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
	{
		free(*(void **)mlx->ptr);
		free(mlx->ptr);
	}
	exit(0);
}
