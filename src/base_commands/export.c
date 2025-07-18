/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:55:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:59:27 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base_commands.h"
#include "shared.h"
#include <unistd.h>

void	ft_export(char **argv, t_list **envp)
{
	int	i;
	int	exit_status;

	if (!argv || !envp)
	{
		g_status_code = 1;
		return ;
	}
	if (!argv[1])
	{
		if (envp && *envp)
			print_exported_vars(*envp);
		g_status_code = 0;
		return ;
	}
	exit_status = 0;
	i = 1;
	while (argv[i])
	{
		if (export_variable(argv[i], envp) != 0)
			exit_status = 1;
		i++;
	}
	g_status_code = exit_status;
}
