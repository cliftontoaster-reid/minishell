/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:51:56 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/01 13:36:41 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "pipex.h"

//static void   exit_failure_free_all(TODO)

void ft_cmdpathlist(t_cmd *cmd, t_list *tenvp)
{   
	t_iteration iter;

	cmd->cmdpathlist = malloc(sizeof(char *) * cmd->cmdnbr);
	if (!cmd->cmdpathlist)
	{
		write(1, "malloc failure\n", 15);
		g_status_code = 12;
		cmd->error = 1;
		return ;
	}
	iter.i = 0;
	while (cmd[iter.i].args)
	{
		cmd->cmdpathlist[iter.i] = ft_get_cmd_path(cmd[iter.i].args[0], tenvp);
		if (!cmd->cmdpathlist[iter.i])
		{
			printf("%s: command not found\n", cmd[iter.i].args[0]);
			g_status_code = 127;
			cmd->error = 1;
		}
		iter.i++;
	}
}
