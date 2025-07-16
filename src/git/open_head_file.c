/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_head_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:08:08 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "git.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

char	*open_head_file(char *git_dir)
{
	char	*head_file;
	int		fd;
	char	*fd_str;

	head_file = ft_strjoin(git_dir, "/HEAD");
	free(git_dir);
	if (!head_file)
		return (NULL);
	fd = open(head_file, O_RDONLY);
	if (fd < 0)
	{
		free(head_file);
		return (NULL);
	}
	fd_str = ft_itoa(fd);
	free(head_file);
	return (fd_str);
}
