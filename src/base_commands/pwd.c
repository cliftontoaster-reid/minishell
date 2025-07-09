/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:55:23 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/09 11:07:45 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	ft_pwd(t_list **envp)
{
	char	**pwd;

	pwd = b_getenv("PWD", *envp);
	if (pwd && pwd[0])
	{
		printf("%s\n", pwd[0]);
		free(pwd[0]);
		free(pwd);
		g_status_code = 0;
	}
	else
	{
		write(2, "pwd: error retrieving current directory\n", 40);
		g_status_code = 1;
	}
}
