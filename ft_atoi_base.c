/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 10:27:59 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 11:40:14 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_error(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(str) < 2)
		return (1);
	while (str[i] && !is_space(str[i]) && str[i] != '+' && str[i] != '-')
	{
		j = i + 1;
		while (str[j] && str[j] != str[i])
			j++;
		if (str[j])
			return (1);
		i++;
	}
	if (str[i])
		return (1);
	return (0);
}

int	is_inbase(char c, char *base)
{
	int	index;

	index = 0;
	while (base[index])
	{
		if (c == base[index])
			return (index);
		index++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	nb;
	int	sign;
	int	base_len;

	nb = 0;
	sign = 1;
	if (is_error(base))
		return (0);
	base_len = ft_strlen(base);
	while (is_space(*str))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (is_inbase(*str, base) != -1)
	{
		nb = (nb * base_len) + is_inbase(*str, base);
		str++;
	}
	return (sign * nb);
}
