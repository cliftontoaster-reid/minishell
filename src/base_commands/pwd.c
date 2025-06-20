/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:55:23 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/20 14:50:37 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void	ft_pwd(char **envp)
{
	int	iteri;
	int	iterj;

	iteri = 0;
	iterj = 4;
	while (envp[iteri] && ft_strncmp(envp[iteri], "PWD=", 4))
		//---------------- strncmp TODO
		iteri++;
	if (!envp[iteri])
		return ;
	while (envp[iteri][iterj])
		write(1, &envp[iteri][iterj++], 1);
	write(1, "\n", 1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_pwd(envp);
	return (0);
}
