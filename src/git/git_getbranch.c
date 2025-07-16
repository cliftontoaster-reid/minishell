/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_getbranch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 13:38:50 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "git.h"
#include "libft.h"
#include <stdlib.h>

// Read current branch from .git/HEAD
char	*git_getbranch(void)
{
	char	*git_dir;
	char	*head_file_fd_str;
	int		fd;
	char	*buffer;
	char	*branch;

	git_dir = find_git_dir();
	if (!git_dir)
		return (NULL);
	head_file_fd_str = open_head_file(git_dir);
	if (!head_file_fd_str)
		return (NULL);
	fd = ft_atoi(head_file_fd_str);
	free(head_file_fd_str);
	buffer = read_head_file(fd);
	if (!buffer)
		return (NULL);
	branch = get_branch_name(buffer, ft_strlen(buffer));
	free(buffer);
	return (branch);
}
