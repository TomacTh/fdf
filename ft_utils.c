/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:28:37 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/10 15:53:24 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	if (s1 && !s2)
		len = ft_strlen(s1);
	else if (!s1 && s2)
		len = ft_strlen(s2);
	else if (!s1 && !s2)
		len = 0;
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (s1)
		ft_strcat(res, s1);
	if (s2)
		ft_strcat(res, s2);
	return (res);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	dst_len;
	int	src_len;

	dst_len = 0;
	src_len = 0;
	while (dest[dst_len])
		++dst_len;
	if (src)
	{
		while (src[src_len])
		{
			dest[dst_len + src_len] = src[src_len];
			++src_len;
		}
		dest[dst_len + src_len] = 0;
	}
	return (dest);
}

