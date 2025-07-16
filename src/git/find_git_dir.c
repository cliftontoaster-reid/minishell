/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_git_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:07:54 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "git.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// Find the .git directory by traversing up from CWD
static char	*find_git_dir_loop(char *cwd)
{
	char		*path;
	struct stat	st;
	char		*slash;

	while (1)
	{
		path = ft_strjoin(cwd, "/.git");
		if (!path)
			break ;
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			return (path);
		free(path);
		slash = ft_strrchr(cwd, '/');
		if (!slash)
			break ;
		*slash = '\0';
	}
	return (NULL);
}

char	*find_git_dir(void)
{
	char	*cwd;
	char	*result;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	result = find_git_dir_loop(cwd);
	free(cwd);
	return (result);
}
