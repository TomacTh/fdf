/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:21:21 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 14:30:41 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	fill_color_line(t_point *point, char **strs)
{
	char	*str_color;

	str_color = 0;
	if (tab_len((void **)strs) == 2)
	{
		str_color = strs[1];
		if ((ft_strlen(str_color) > 2))
		{
			if (!ft_strncmp(str_color, "0x", 2))
			{
				str_color = ft_str_tolower(str_color);
				point->color = ft_atoi_base(&str_color[2], "0123456789abcdef");
			}
			else
				point->color = ft_atoi(str_color);
			if (! point->color)
				point->color = 0x00ffffff;
		}
	}
	else
		point->color = 0x00ffffff;
}

int	fill_map_line(t_fdf *fdf, char *str, char **strs, unsigned int len)
{
	unsigned int	i;
	char			**strs_color;

	i = 0;
	if (!protect_malloc((void **)&fdf->map[len], sizeof(t_point) * fdf->width))
		return (recursive_error(str, strs, len - 1, fdf));
	while (strs[i])
	{
		fdf->map[len][i].z = ft_atoi(strs[i]);
		strs_color = ft_split(strs[i], ',');
		if (!strs_color)
		{
			free_split(strs_color, -1);
			return (recursive_error(str, strs, len, fdf));
		}
		fill_color_line(&fdf->map[len][i], strs_color);
		free_split(strs_color, -1);
		++i;
	}
	free(str);
	free_split(strs, -1);
	return (0);
}

int	eof_recursion(t_fdf *fdf, char *str, unsigned int len)
{
	char	**strs;

	strs = 0;
	fdf->height = len;
	if (*str)
		++fdf->height;
	if (!protect_malloc((void **)&fdf->map, sizeof(t_point *) * fdf->height))
		return (recursive_error(str, strs, len, fdf));
	if (*str)
	{
		strs = ft_split(str, ' ');
		if (!strs)
			return (recursive_error(str, strs, len + 1, fdf));
		fdf->width = tab_len((void **)strs);
		fill_map_line(fdf, str, strs, len);
	}
	else
		free(str);
	return (0);
}

int	destack_recursion(t_fdf *fdf, char *str, unsigned int len)
{
	char			**strs;
	unsigned int	tablen;

	strs = ft_split(str, ' ');
	if (!strs)
		return (recursive_error(str, strs, len + 1, fdf));
	tablen = tab_len((void **)strs);
	if (!fdf->width)
		fdf->width = tablen;
	else
	{
		if (tablen != fdf->width)
			return (recursive_error(str, strs, len + 1, fdf));
	}
	return (fill_map_line(fdf, str, strs, len));
}

int	recursive_parse(t_fdf *fdf, unsigned int len)
{
	char	*str;
	int		i;

	str = 0;
	if (fdf->error_code)
		return (recursive_error(str, 0, len, fdf));
	i = get_next_line(fdf->fd, &str);
	if (i == -1)
		return (recursive_error(str, 0, len, fdf));
	else
	{
		if (i)
			recursive_parse(fdf, len + 1);
		else
			return (eof_recursion(fdf, str, len));
	}
	if (fdf->error_code)
		return (recursive_error(str, 0, len, fdf));
	return (destack_recursion(fdf, str, len));
}
