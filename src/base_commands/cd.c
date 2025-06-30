/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:58:27 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/27 18:18:06 by lfiorell@st      ###   ########.fr       */
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

	if (argv[1] == NULL)
	{
		write(2, "cd: no such file or directory: ", 31);
		return ;
	}
	if (chdir(argv[1]))
	{
		write(1, "cd: no such file or directory: ", 31);
		write(1, argv[1], ft_strlen(argv[1]));
		write(1, "\n", 1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		b_setenv("PWD", cwd, envp);
	}
	else
	{
		perror("cd: error retrieving current directory");
	}
}
