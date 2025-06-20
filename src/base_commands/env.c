/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:30:46 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/18 11:42:55 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

int	ft_env(char **envp)
{
	int	iteri;

	iteri = 0;
	while (envp[iteri])
	{
		write(1, envp[iteri], strlen(envp[iteri])); // ----------------TODO strlen
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
