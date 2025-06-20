/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:55:23 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/18 09:58:15 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

static void	ft_pwd(char **envp)
{
	int	iteri;
	int	iterj;

	iteri = 0;
	iterj = 4;
	while (envp[iteri] && strncmp(envp[iteri], "PWD=", 4)) //---------------- strncmp TODO
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
	return(0);
}
