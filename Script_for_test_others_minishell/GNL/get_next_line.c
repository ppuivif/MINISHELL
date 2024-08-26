/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:15:24 by ppuivif           #+#    #+#             */
/*   Updated: 2024/06/14 10:52:36 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_line_return(char *s)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*eof(char **buf, char **line, char **tmp)
{
	if (*buf)
	{
		if (find_line_return(*buf) > 0)
		{
			*line = close_current_line(*buf);
			*buf = begin_new_line(*buf);
			free(*tmp);
			*tmp = NULL;
			return (*line);
		}
		*line = ft_get_strjoin(*line, *buf);
		free(*buf);
		*buf = NULL;
		free(*tmp);
		*tmp = NULL;
		return (*line);
	}
	else
	{
		free(*buf);
		*buf = NULL;
		free(*tmp);
		*tmp = NULL;
		return (NULL);
	}
}

static char	*er_or_last_read(int n_bytes, char **tmp, char **buf, char **line)
{
	if (n_bytes == -1)
	{
		free(*tmp);
		*tmp = NULL;
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	*line = eof(&(*buf), &(*line), &(*tmp));
	return (*line);
}

static int	current_line(char **line, char **buf, char **tmp)
{
	*buf = ft_get_strjoin(*buf, *tmp);
	free(*tmp);
	*tmp = NULL;
	if (*buf == NULL)
	{
		*line = NULL;
		return (0);
	}
	if (find_line_return(*buf) > 0)
	{
		*line = close_current_line(*buf);
		*buf = begin_new_line(*buf);
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	int			nb_read_bytes;
	static char	*buf;
	char		*tmp;
	char		*line;

	nb_read_bytes = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
//	write(1, "> ", 2);
	while (1)
	{
		tmp = ft_get_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!tmp)
			return (NULL);
		nb_read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (nb_read_bytes == -1 || nb_read_bytes == 0)
		{
			line = er_or_last_read(nb_read_bytes, &tmp, &buf, &line);
			return (line);
		}
		if (current_line(&line, &buf, &tmp) == 0)
			return (line);
	}
}
