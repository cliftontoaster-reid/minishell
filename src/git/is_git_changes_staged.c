/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_git_changes_staged.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 13:38:50 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "git.h"
#include <sys/wait.h>
#include <unistd.h>

bool	is_git_changes_staged(void)
{
	pid_t		pid;
	int			status;
	char		*argv[6];
	extern char	**environ;

	argv[0] = "git";
	argv[1] = "diff";
	argv[2] = "--staged";
	argv[3] = "--quiet";
	argv[4] = "--exit-code";
	argv[5] = NULL;
	pid = fork();
	if (pid < 0)
		return (false);
	if (pid == 0)
	{
		execve("/usr/bin/git", argv, environ);
		_exit(1);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (false);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status) != 0);
	return (false);
}
