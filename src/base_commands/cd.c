/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:58:27 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/20 14:49:10 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	ft_cd(char **argv, char **envp)
{
	// char cwd[PATH_MAX];
	if (chdir(argv[1]))
	{
		write(1, "cd: no such file or directory: ", 31);
		write(1, argv[1], ft_strlen(argv[1])); //-----------------TODO strlen
		write(1, "\n", 1);
	}
	/*
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current working directory:\n%s\n", cwd);
	*/
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (argc == 2)
		ft_cd(argv, envp);
	return (0);
}
