/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_head_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 13:38:50 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "git.h"
#include <stdlib.h>
#include <unistd.h>

char	*read_head_file(int fd)
{
	char	*buffer;
	ssize_t	n;

	buffer = malloc(256);
	if (!buffer)
		return (NULL);
	n = read(fd, buffer, 255);
	close(fd);
	if (n <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[n] = '\0';
	return (buffer);
}
