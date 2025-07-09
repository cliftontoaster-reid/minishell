/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:13:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/08 19:17:13 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include "utils.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

#define COLOUR_RESET "\001\033[0m\002"
#define COLOUR_YELLOW "\001\033[33m\002"
#define COLOUR_RED "\001\033[31m\002"
#define COLOUR_GREEN "\001\033[32m\002"
#define COLOUR_PINK "\001\033[35m\002"
#define STYLE_BOLD "\001\033[1m\002"
#define STYLE_ITALIC "\001\033[3m\002"
#define STYLE_UNDERLINE "\001\033[4m\002"

#define PROMPT_SYMBOL_ERROR "\001\033[31m\002!\001\033[0m\002"
#define PROMPT_SYMBOL_SUCCESS "\001\033[32m\002$\001\033[0m\002"

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

// Find the .git directory by traversing up from CWD
static char	*find_git_dir(void)
{
	char		*cwd;
	char		*path;
	struct stat	st;
	char		*slash;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	while (1)
	{
		path = ft_strjoin(cwd, "/.git");
		if (!path)
			break ;
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			free(cwd);
			return (path);
		}
		free(path);
		{
			slash = ft_strrchr(cwd, '/');
			if (!slash)
				break ;
			*slash = '\0';
		}
	}
	free(cwd);
	return (NULL);
}

// Check if current directory is inside a git repository
static bool	is_repo(void)
{
	char	*gd;

	gd = find_git_dir();
	if (gd)
	{
		free(gd);
		return (true);
	}
	return (false);
}

static char	*get_branch_name(char *buffer, ssize_t n)
{
	char	*newline;
	size_t	len;

	if (ft_strncmp(buffer, "ref: refs/heads/", 16) == 0)
	{
		newline = ft_strchr(buffer, '\n');
		len = newline ? (size_t)(newline - (buffer + 16)) : (size_t)(n - 16);
		return (ft_strndup(buffer + 16, len));
	}
	else
		return (ft_strndup(buffer, (n > 7 ? 7 : (size_t)n)));
}

static char	*read_head_file(int fd)
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

static char	*open_head_file(char *git_dir)
{
	char	*head_file;
	int		fd;

	head_file = ft_strjoin(git_dir, "/HEAD");
	free(git_dir);
	if (!head_file)
		return (NULL);
	fd = open(head_file, O_RDONLY);
	free(head_file);
	if (fd < 0)
		return (NULL);
	return (head_file ? ft_itoa(fd) : NULL);
}

// Read current branch from .git/HEAD
static char	*git_getbranch(void)
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

/// {symbol} [green] [italic] [bold] [underline] dirname [reset] (if git repo) git:[branch[ *]]

static bool	is_git_changes(void)
{
	pid_t		pid;
	int			status;
	char		*argv[5];
	extern char	**environ;

	argv[0] = "git";
	argv[1] = "diff";
	argv[2] = "--quiet";
	argv[3] = "--exit-code";
	argv[4] = NULL;
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

static bool	is_git_changes_staged(void)
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

static void	git_message(void)
{
	char	*branch;
	bool	uncommitted_changes;
	bool	staged_changes;

	branch = git_getbranch();
	if (branch)
	{
		ft_putstr_fd(" (git: " COLOUR_YELLOW, STDOUT_FILENO);
		ft_putstr_fd(branch, STDOUT_FILENO);
		uncommitted_changes = is_git_changes();
		staged_changes = is_git_changes_staged();
		if (uncommitted_changes || staged_changes)
			ft_putstr_fd(COLOUR_PINK "*", STDOUT_FILENO);
		if (uncommitted_changes)
			ft_putstr_fd(COLOUR_RED "!", STDOUT_FILENO);
		ft_putstr_fd(COLOUR_RESET ")", STDOUT_FILENO);
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
	ft_putstr_fd(STYLE_ITALIC STYLE_BOLD STYLE_UNDERLINE, STDOUT_FILENO);
	ft_putstr_fd(dirname, STDOUT_FILENO);
	ft_putstr_fd(COLOUR_RESET, STDOUT_FILENO);
	if (is_repo())
		git_message();
	ft_putstr_fd("\n" STYLE_ITALIC, STDOUT_FILENO);
	free(dirname);
}
