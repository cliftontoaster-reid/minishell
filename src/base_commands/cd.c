/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:21:40 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/28 10:42:15 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 4096

static void	set_oldpwd(t_list **envp)
{
	char	**cwd;

	cwd = b_getenv("PWD", *envp);
	if (cwd && *cwd)
	{
		b_setenv("OLDPWD", *cwd, envp);
		free(*cwd);
		free(cwd);
	}
	else
	{
		write(2, "cd: PWD not set\n", 16);
		g_status_code = 1;
		return ;
	}
}

void	cd_go_home(t_list **envp)
{
	char	**home_env;

	home_env = b_getenv("HOME", *envp);
	if (!home_env)
	{
		write(2, "cd: HOME not set\n", 18);
		g_status_code = 1;
		return ;
	}
	if (chdir(*home_env) != 0)
	{
		perror("cd");
		g_status_code = 1;
		return ;
	}
	free(home_env[0]);
	free(home_env);
}

static void	cd_go_previous(t_list **envp)
{
	char	**oldpwd_env;

	oldpwd_env = b_getenv("OLDPWD", *envp);
	if (!oldpwd_env)
	{
		write(2, "cd: OLDPWD not set\n", 19);
		g_status_code = 1;
		return ;
	}
	if (chdir(*oldpwd_env) != 0)
	{
		perror("cd");
		g_status_code = 1;
		return ;
	}
	free(oldpwd_env[0]);
	free(oldpwd_env);
}

void	cd_go_to_path(char **argv)
{
	if (chdir(argv[1]) != 0)
	{
		write(1, "cd: no such file or directory: ", 31);
		write(1, argv[1], ft_strlen(argv[1]));
		write(1, "\n", 1);
		g_status_code = 1;
		return ;
	}
	else
	{
		g_status_code = 0;
	}
}

void	ft_cd(char **argv, t_list **envp)
{
	char	cwd[PATH_MAX];

	if (argv[1] == NULL)
		cd_go_home(envp);
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		cd_go_previous(envp);
	else
		cd_go_to_path(argv);
	set_oldpwd(envp);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		b_setenv("PWD", cwd, envp);
	}
	else
	{
		perror("cd: error retrieving current directory");
		g_status_code = 1;
	}
}
