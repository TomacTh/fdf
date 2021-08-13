/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:55:57 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 17:48:45 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

static int	error(char **buff, char **line, int fd)
{
	*buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!*buff || !line || BUFFER_SIZE <= 0 || fd < 0 || fd > 256)
	{
		if (*buff)
			free(*buff);
		return (-1);
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr && *ptr != (unsigned char)c)
		++ptr;
	if (*ptr == (unsigned char)c)
		return (ptr);
	return (0);
}

static char	*new_line(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strchr(str, '\n'));
}

static int	split_line(char **line, char **content)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while ((*content)[i] && (*content)[i] != '\n')
		++i;
	if ((*content)[i] == '\0')
	{
		(*line) = ft_strdup(*content);
		free(*content);
		(*content) = NULL;
		return (0);
	}
	tmp = (*content);
	(*line) = ft_strndup(tmp, i);
	(*content) = ft_strdup(tmp + i + 1);
	free(tmp);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*content[256];
	char		*buff;
	char		*tmp;
	int			rlen;

	rlen = 1;
	if (error(&buff, line, fd))
		return (-1);
	while (!new_line(content[fd]) && rlen > 0)
	{
		rlen = read(fd, buff, BUFFER_SIZE);
		buff[rlen] = 0;
		tmp = content[fd];
		content[fd] = ft_strjoin(content[fd], buff);
		free(tmp);
	}
	free(buff);
	if (rlen < 0)
		return (-1);
	return (split_line(line, &content[fd]));
}
