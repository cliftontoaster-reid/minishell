/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:30:46 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/20 14:49:56 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <unistd.h>

int	ft_env(char **envp)
{
	int	iteri;

	iteri = 0;
	while (envp[iteri])
	{
		write(1, envp[iteri], ft_strlen(envp[iteri]));
			// ----------------TODO strlen
		write(1, "\n", 1);
		iteri++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_env(envp);
	return (0);
}
