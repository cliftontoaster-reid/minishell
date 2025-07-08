/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:13:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/08 11:28:01 by lfiorell@st      ###   ########.fr       */
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

#define COLOUR_RESET ("\033[0m")
#define COLOUR_YELLOW ("\033[33m")
#define COLOUR_RED ("\033[31m")
#define COLOUR_GREEN ("\033[32m")
#define COLOUR_PINK ("\033[35m")
#define STYLE_BOLD ("\033[1m")
#define STYLE_ITALIC ("\033[3m")
#define STYLE_UNDERLINE ("\033[4m")

#define PROMPT_SYMBOL_ERROR ("\033[31m!\033[0m")
#define PROMPT_SYMBOL_SUCCESS ("\033[32m$\033[0m")

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

// Read current branch from .git/HEAD
static char	*git_getbranch(void)
{
	char	*git_dir;
	char	*head_file;
	char	*buffer;
	char	*branch;
	int		fd;
	ssize_t	n;
	char	*newline;
	size_t	len;

	git_dir = find_git_dir();
	if (!git_dir)
		return (NULL);
	head_file = ft_strjoin(git_dir, "/HEAD");
	free(git_dir);
	if (!head_file)
		return (NULL);
	fd = open(head_file, O_RDONLY);
	free(head_file);
	if (fd < 0)
		return (NULL);
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
	if (ft_strncmp(buffer, "ref: refs/heads/", 16) == 0)
	{
		newline = ft_strchr(buffer, '\n');
		len = newline ? (size_t)(newline - (buffer + 16)) : (size_t)(n - 16);
		branch = ft_strndup(buffer + 16, len);
	}
	else
		branch = ft_strndup(buffer, (n > 7 ? 7 : (size_t)n));
	free(buffer);
	return (branch);
}

/// {symbol} [green] [italic] [bold] [underline] dirname [reset] (if git repo) git:[branch]

static void	git_message(t_list *env)
{
	char	*branch;

	(void)env; // no longer needed
	branch = git_getbranch();
	if (branch)
	{
		ft_putstr_fd(" (git: ", STDOUT_FILENO);
		ft_putstr_fd(COLOUR_YELLOW, STDOUT_FILENO);
		ft_putstr_fd(branch, STDOUT_FILENO);
		ft_putstr_fd(COLOUR_RESET, STDOUT_FILENO);
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
	if (is_repo())
		git_message(env);
	ft_putstr_fd("\n > ", STDOUT_FILENO);
	free(dirname);
}
