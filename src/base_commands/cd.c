/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:21:40 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/15 16:19:15 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 4096

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

void	ft_cd(char **argv, t_list **envp)
{
	char	cwd[PATH_MAX];

	if (argv[1] == NULL)
		cd_go_home(envp);
	else
	{
		if (chdir(argv[1]) != 0)
		{
			write(1, "cd: no such file or directory: ", 31);
			write(1, argv[1], ft_strlen(argv[1]));
			write(1, "\n", 1);
			g_status_code = 1;
			return ;
		}
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		b_setenv("PWD", cwd, envp);
		g_status_code = 0;
	}
	else
	{
		perror("cd: error retrieving current directory");
		g_status_code = 1;
	}
}
