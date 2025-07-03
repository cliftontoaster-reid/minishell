/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opentmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:00:55 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/02 14:23:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

static char	*generate_tmp_path(int rand_fd)
{
	char	*tmpid;
	char	*path;

	tmpid = ft_readstr(rand_fd, 16);
	if (!tmpid)
		return (NULL);
	path = ft_strjoin("/tmp/minishell_heredoc_", tmpid);
	free(tmpid);
	return (path);
}

static int	create_tmp_file(const char *path)
{
	int	file_fd;

	file_fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0600);
	return (file_fd);
}

static t_file	*create_file_struct(int file_fd, char *path)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->fd = file_fd;
	file->path = path;
	return (file);
}

static void	cleanup_on_error(int file_fd, char *path, bool auto_unlink)
{
	close(file_fd);
	if (!auto_unlink)
		unlink(path);
	free(path);
}

t_file	*ft_opentmp(int rand_fd, bool auto_unlink)
{
	char	*path;
	int		file_fd;
	t_file	*file;

	path = generate_tmp_path(rand_fd);
	if (!path)
		return (NULL);
	file_fd = create_tmp_file(path);
	if (file_fd == -1)
	{
		free(path);
		return (NULL);
	}
	if (auto_unlink)
		unlink(path);
	file = create_file_struct(file_fd, path);
	if (!file)
	{
		cleanup_on_error(file_fd, path, auto_unlink);
		return (NULL);
	}
	return (file);
}
