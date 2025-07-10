/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:30:46 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/10 14:34:41 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include <string.h>
#include <unistd.h>

void	ft_env(t_list **env)
{
	int		iteri;
	char	**envp;

	iteri = 0;
	envp = b_getenv(NULL, *env);
	if (!envp)
	{
		write(2, "env: no environment variables found\n", 36);
		g_status_code = 1;
		return ;
	}
	while (envp[iteri])
	{
		write(1, envp[iteri], ft_strlen(envp[iteri]));
		write(1, "\n", 1);
		iteri++;
	}
	g_status_code = 0;
}
