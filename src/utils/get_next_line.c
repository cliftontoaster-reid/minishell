/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:01:00 by creid             #+#    #+#             */
/*   Updated: 2025/07/23 20:08:05 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

/**
 * @brief Reads data from file descriptor and appends to buffer
 * @param fd File descriptor to read from
 * @param buffer Current buffer content
 * @return Updated buffer with new data, or NULL on error
 */
static char	*read_and_join(int fd, char *buffer)
{
	char	*temp_buffer;
	char	*joined;
	ssize_t	bytes_read;

	temp_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buffer)
		return (NULL);
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(temp_buffer);
		return (NULL);
	}
	temp_buffer[bytes_read] = '\0';
	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer)
	{
		free(temp_buffer);
		return (NULL);
	}
	joined = ft_strjoin(buffer, temp_buffer);
	free(buffer);
	free(temp_buffer);
	return (joined);
}

/**
 * @brief Extracts a line from buffer up to newline character
 * @param buffer Buffer containing data
 * @return Extracted line excluding newline, or NULL if no line found
 */
static char	*extract_line_from_buffer(char *buffer)
{
	char	*newline_pos;
	char	*line;
	size_t	line_len;

	if (!buffer || !*buffer)
		return (NULL);
	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos)
	{
		line_len = newline_pos - buffer;
		line = ft_substr(buffer, 0, line_len);
		return (line);
	}
	line = ft_strdup(buffer);
	return (line);
}

/**
 * @brief Updates buffer by removing the extracted line
 * @param buffer Current buffer
 * @return Updated buffer with line removed, or NULL if buffer is empty
 */
static char	*update_buffer(char *buffer)
{
	char	*newline_pos;
	char	*new_buffer;

	if (!buffer)
		return (NULL);
	newline_pos = ft_strchr(buffer, '\n');
	if (!newline_pos)
	{
		free(buffer);
		return (NULL);
	}
	if (*(newline_pos + 1) == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(newline_pos + 1);
	free(buffer);
	return (new_buffer);
}

/**
 * @brief Fills the buffer until it contains a newline or EOF
 * @param fd      File descriptor to read from
 * @param buffer  Current buffer content (may be NULL)
 * @return        Updated buffer containing at least one newline, or
 *                the remaining data on EOF, or NULL on error/empty EOF
 */
static char	*fill_buffer(int fd, char *buffer)
{
	while (!buffer || !ft_strchr(buffer, '\n'))
	{
		buffer = read_and_join(fd, buffer);
		if (!buffer)
			return (NULL);
		if (!ft_strchr(buffer, '\n') && ft_strlen(buffer) == 0)
		{
			free(buffer);
			return (NULL);
		}
		if (!ft_strchr(buffer, '\n') && ft_strlen(buffer) > 0)
			break ;
	}
	return (buffer);
}

/**
 * @brief Reads the next line (excluding newline) from fd
 * @param fd     File descriptor to read from
 * @param buffer Pointer to buffer pointer for maintaining state between calls
 * @return       The next line, or NULL on EOF/error
 *
 * Uses the provided buffer pointer to preserve unread data between calls.
 */
char	*get_next_line(int fd, char **buffer)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
		return (NULL);
	*buffer = fill_buffer(fd, *buffer);
	if (!*buffer)
		return (NULL);
	line = extract_line_from_buffer(*buffer);
	*buffer = update_buffer(*buffer);
	return (line);
}
