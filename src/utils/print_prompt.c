/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:13:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/04 14:10:09 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include "utils.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#define COLOUR_RESET "\033[0m"
#define COLOUR_YELLOW "\033[33m"
#define COLOUR_RED "\033[31m"
#define COLOUR_GREEN "\033[32m"
#define COLOUR_PINK "\033[35m"
#define STYLE_BOLD "\033[1m"
#define STYLE_ITALIC "\033[3m"
#define STYLE_UNDERLINE "\033[4m"

#define PROMPT_SYMBOL_ERROR "\033[31m!\033[0m"
#define PROMPT_SYMBOL_SUCCESS "\033[32m$\033[0m"

static char	*get_dirname(t_list *env)
{
	char	**pwd;
	char	*last_slash;
	char	*res;

	pwd = b_getenv("PWD", env);
	if (pwd == NULL)
		return (ft_strdup("unknown"));
	last_slash = ft_strrchr(*pwd, '/');
	if (last_slash != NULL)
		res = ft_strdup(last_slash + 1);
	else
		res = ft_strdup(*pwd);
	if (res != NULL)
	{
		free(*pwd);
		free(pwd);
	}
	return (res);
}

static void	redirect_output_to_devnull(void)
{
	int	devnull;

	devnull = open("/dev/null", O_WRONLY);
	if (devnull != -1)
	{
		dup2(devnull, STDOUT_FILENO);
		dup2(devnull, STDERR_FILENO);
		close(devnull);
	}
	else
	{
		ft_putstr_fd("Error opening /dev/null\n", STDERR_FILENO);
		exit(1);
	}
}

// Runs `git rev-parse --is-inside-work-tree` to check if the
// current directory is a git repository
// if it returns status code 0, it is a git repository,
//	it must use fork and execve
static bool	is_repo(t_list *env)
{
	int		status;
	pid_t	pid;
	char	*cmd[4];
	char	**envp;

	cmd[0] = "git";
	cmd[1] = "rev-parse";
	cmd[2] = "--is-inside-work-tree";
	cmd[3] = NULL;
	envp = b_getenv(NULL, env);
	pid = fork();
	if (pid == 0)
	{
		redirect_output_to_devnull();
		execve("/usr/bin/git", cmd, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (true);
	return (false);
}

static bool	git_changes(t_list *env)
{
	int		status;
	pid_t	pid;
	char	*cmd[4];
	char	**envp;

	cmd[0] = "git";
	cmd[1] = "diff";
	cmd[2] = "--quiet";
	cmd[3] = NULL;
	envp = b_getenv(NULL, env);
	pid = fork();
	if (pid == 0)
	{
		redirect_output_to_devnull();
		execve("/usr/bin/git", cmd, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (false);
	return (true);
}

static char	*read_from_pipe(int fd)
{
	char	buffer[256];
	char	*res;
	char	*tmp;
	ssize_t	n;

	res = NULL;
	while ((n = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[n] = '\0';
		if (!res)
			res = ft_strdup(buffer);
		else
		{
			tmp = res;
			res = ft_strjoin(res, buffer);
			free(tmp);
		}
		if (!res)
			return (NULL);
	}
	if (!res)
		return (ft_strdup(""));
	if ((tmp = ft_strchr(res, '\n')))
		*tmp = '\0';
	return (res);
}

static char	*git_getbranch(t_list *env)
{
	int		status;
	pid_t	pid;
	int		pipefd[2];
	char	*cmd[5];
	char	*branch;

	cmd[0] = "git";
	cmd[1] = "rev-parse";
	cmd[2] = "--abbrev-ref";
	cmd[3] = "HEAD";
	cmd[4] = NULL;
	branch = NULL;
	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve("/usr/bin/git", cmd, b_getenv(NULL, env));
		exit(1);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		branch = read_from_pipe(pipefd[0]);
	close(pipefd[0]);
	return (branch);
}

/// {symbol} [green] [italic] [bold] [underline] dirname [reset] (if git repo) git:[branch]

static void	git_message(t_list *env)
{
	char	*branch;

	branch = git_getbranch(env);
	if (branch)
	{
		ft_putstr_fd(" (git: ", STDOUT_FILENO);
		ft_putstr_fd(COLOUR_YELLOW, STDOUT_FILENO);
		ft_putstr_fd(branch, STDOUT_FILENO);
		ft_putstr_fd(COLOUR_RESET, STDOUT_FILENO);
		if (git_changes(env))
		{
			ft_putstr_fd(COLOUR_PINK, STDOUT_FILENO);
			ft_putstr_fd(" *", STDOUT_FILENO);
			ft_putstr_fd(COLOUR_RESET, STDOUT_FILENO);
		}
		else
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(")", STDOUT_FILENO);
		free(branch);
	}
}

void	print_prompt(t_list *env)
{
	char	*dirname;

	dirname = get_dirname(env);
	if (g_status_code == 0)
		ft_putstr_fd(PROMPT_SYMBOL_SUCCESS, STDOUT_FILENO);
	else
		ft_putstr_fd(PROMPT_SYMBOL_ERROR, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	if (g_status_code == 0)
		ft_putstr_fd(COLOUR_GREEN, STDOUT_FILENO);
	else
		ft_putstr_fd(COLOUR_RED, STDOUT_FILENO);
	ft_putstr_fd(STYLE_ITALIC, STDOUT_FILENO);
	ft_putstr_fd(STYLE_BOLD, STDOUT_FILENO);
	ft_putstr_fd(STYLE_UNDERLINE, STDOUT_FILENO);
	ft_putstr_fd(dirname, STDOUT_FILENO);
	ft_putstr_fd(COLOUR_RESET, STDOUT_FILENO);
	if (is_repo(env))
		git_message(env);
	ft_putstr_fd(" > ", STDOUT_FILENO);
	free(dirname);
}
