/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:13:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:13:23 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "git.h"
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
#define COLOUR_RED "\001\033[31m\002"
#define COLOUR_GREEN "\001\033[32m\002"
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
