/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_getpid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:14:15 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:20:15 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int	read_proc_stat(char *buf, size_t bufsize)
{
	int		fd;
	ssize_t	n;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	n = read(fd, buf, bufsize - 1);
	if (n < 0)
	{
		perror("read");
		close(fd);
		return (-1);
	}
	buf[n] = '\0';
	close(fd);
	return (0);
}

static pid_t	parse_pid_from_stat(const char *buf)
{
	int			pid;
	const char	*p = buf;

	pid = 0;
	while (*p && (*p < '0' || *p > '9'))
		p++;
	while (*p >= '0' && *p <= '9')
	{
		pid = pid * 10 + (*p - '0');
		p++;
	}
	return (pid);
}

pid_t	b_getpid(void)
{
	char	buf[64];

	if (read_proc_stat(buf, sizeof(buf)) < 0)
		return (-1);
	return (parse_pid_from_stat(buf));
}
