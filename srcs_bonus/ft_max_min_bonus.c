/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_min_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:13:39 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 19:50:53 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

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
