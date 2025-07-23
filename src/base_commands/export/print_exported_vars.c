/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exported_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 17:59:41 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base_commands.h"
#include "shared.h"
#include <unistd.h>

void	print_exported_vars(t_list *envp)
{
	char	**env_vars;
	int		i;

	if (!envp)
		return ;
	env_vars = b_getenv(NULL, envp);
	if (!env_vars)
		return ;
	i = 0;
	while (env_vars[i])
	{
		if (write(1, "declare -x ", 11) == -1)
			break ;
		if (write(1, env_vars[i], ft_strlen(env_vars[i])) == -1)
			break ;
		if (write(1, "\n", 1) == -1)
			break ;
		free(env_vars[i]);
		i++;
	}
	while (env_vars[i])
		free(env_vars[i++]);
	free(env_vars);
}
