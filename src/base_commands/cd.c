/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:21:40 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/07 17:52:13 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 4096

void	ft_cd(char **argv, t_list **envp)
{
	char	cwd[PATH_MAX];
	char 	*home;

	if (argv[1] == NULL)
	{
		home = *b_getenv("HOME", *envp);
		if (!home)
		{
			write(2, "cd: HOME not set\n", 18);
			return ;
		}
		if (chdir(home) != 0)
		{
			perror("cd");
			return ;
		}
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			write(1, "cd: no such file or directory: ", 31);
			write(1, argv[1], ft_strlen(argv[1]));
			write(1, "\n", 1);
			return ;
		}
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		b_setenv("PWD", cwd, envp);
		g_status_code = 0;
	}
	else
		perror("cd: error retrieving current directory");
}
