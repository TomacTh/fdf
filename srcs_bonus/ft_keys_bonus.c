/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 19:14:31 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 19:17:49 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

void	zoom_or_dezoom_key(int keycode, t_moove *moove)
{	
	if (keycode == ZOOM)
	{
		moove->zoom = 1;
		moove->dezoom = 0;
	}
	else if (keycode == DEZOOM)
	{
		moove->zoom = 0;
		moove->dezoom = 1;
	}
}

void	shift_bottom_and_up(int keycode, t_moove *moove)
{
	if (keycode == SHIFT_UP)
	{
		moove->add_shifty = 0;
		moove->less_shifty = 1;
	}
	else if (keycode == SHIFT_BOTTOM)
	{
		moove->add_shifty = 1;
		moove->less_shifty = 0;
	}
}

void	shift_left_and_right(int keycode, t_moove *moove)
{
	if (keycode == SHIFT_LEFT)
	{
		moove->add_shiftx = 0;
		moove->less_shiftx = 1;
	}
	else if (keycode == SHIFT_RIGHT)
	{
		moove->add_shiftx = 1;
		moove->less_shiftx = 0;
	}
}

void	shift_keys(int keycode, t_moove *moove)
{
	if (keycode == SHIFT_BOTTOM || keycode == SHIFT_UP)
		shift_bottom_and_up(keycode, moove);
	else if (keycode == SHIFT_RIGHT || keycode == SHIFT_LEFT)
		shift_left_and_right(keycode, moove);
}

void	z_depth_keys(int keycode, t_moove *moove)
{
	if (keycode == Z_DEPTH_MORE)
	{
		moove->add_z_depth = 1;
		moove->less_z_depth = 0;
	}
	else if (keycode == Z_DEPTH_LESS)
	{
		moove->add_z_depth = 0;
		moove->less_z_depth = 1;
	}
}
