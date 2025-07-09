/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:51:56 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/09 10:31:06 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "pipex.h"

//static void   exit_failure_free_all(TODO)

static int	ft_check_if_builtin(t_cmd *cmd, int cmd_idx)
{
	if (!ft_strncmp(cmd[cmd_idx].args[0], "cd", 3)
		|| !ft_strncmp(cmd[cmd_idx].args[0], "echo", 5)
		|| !ft_strncmp(cmd[cmd_idx].args[0], "env", 4)
		|| !ft_strncmp(cmd[cmd_idx].args[0], "exit", 5)
		|| !ft_strncmp(cmd[cmd_idx].args[0], "export", 7)
		|| !ft_strncmp(cmd[cmd_idx].args[0], "pwd", 4)
		|| !ft_strncmp(cmd[cmd_idx].args[0], "unset", 6))
		return (1);
	return (0);
}

void ft_cmdpathlist(t_cmd *cmd, t_list *env)
{   
	t_iteration iter;

	cmd->cmdpathlist = malloc(sizeof(char *) * cmd->cmdnbr);
	if (!cmd->cmdpathlist)
	{
		write(1, "malloc failure\n", 15);
		cmd->error = 12;
		return ;
	}
	iter.i = 0;
	while (cmd[iter.i].args)
	{
		cmd->cmdpathlist[iter.i] = ft_get_cmd_path(cmd[iter.i].args[0], env);
		if (!cmd->cmdpathlist[iter.i]
			&& !ft_check_if_builtin(cmd, iter.i))
		{
			printf("%s: command not found\n", cmd[iter.i].args[0]);
			cmd->error = 127;
		}
		iter.i++;
	}
}
