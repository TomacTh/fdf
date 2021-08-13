/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:13:25 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 14:30:41 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

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
