/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 17:46:59 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 17:47:02 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	size *= count;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	size;

	size = ft_strlen(s);
	new = ft_calloc(sizeof(char) * (size + 1), 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, size);
	return (new);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdst;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (dst != src)
	{
		while (n--)
		{
			*pdst = *psrc;
			++pdst;
			++psrc;
		}
	}
	return (dst);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

int	ft_atoi(const char *str)
{
	int		num;
	int		sign;

	num = 0;
	sign = 1;
	while ((*(char *)str >= '\t' && *(char *)str <= '\r')
		|| *(char *)str == ' ')
		str++;
	if (*(char *)str == '-' || *(char *)str == '+')
	{
		if (*(char *)str == '-')
			sign = -1;
		str++;
	}
	while (*(char *)str >= '0' && *(char *)str <= '9')
	{
		num = num * 10 + (*(char *)str - '0');
		str++;
	}
	return (num * sign);
}
