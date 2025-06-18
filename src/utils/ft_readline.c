/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:59:04 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/18 13:07:23 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 1

static char	*read_and_append(int fd, char *saved)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (saved);
	}
	buffer[bytes_read] = '\0';
	temp = ft_strjoin_free(saved, buffer);
	return (temp);
}

static char	*extract_line(char **saved)
{
	char	*line;
	char	*newline_pos;
	char	*temp;
	size_t	line_len;

	if (!*saved)
		return (NULL);
	newline_pos = ft_strchr(*saved, '\n');
	if (newline_pos)
	{
		line_len = newline_pos - *saved + 1;
		line = ft_substr(*saved, 0, line_len);
		temp = ft_strdup(newline_pos + 1);
		free(*saved);
		*saved = temp;
		return (line);
	}
	line = ft_strdup(*saved);
	free(*saved);
	*saved = NULL;
	return (line);
}

char	*ft_readline(t_linereader *reader)
{
	static char	*saved = NULL;
	char		*line;

	if (!reader || reader->fd < 0)
		return (NULL);
	while (!ft_strchr(saved, '\n'))
	{
		saved = read_and_append(reader->fd, saved);
		if (!saved)
			return (NULL);
		if (!ft_strchr(saved, '\n') && ft_strlen(saved) == 0)
		{
			free(saved);
			saved = NULL;
			return (NULL);
		}
	}
	line = extract_line(&saved);
	if (reader->line)
		free(reader->line);
	if (line)
		reader->line = ft_strdup(line);
	else
		reader->line = NULL;
	return (line);
}
