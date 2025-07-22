/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:34:25 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/22 16:18:15 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "shared.h"
#include "utils.h"
#include <unistd.h>

void	ft_cleanup_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmdpathlist)
	{
		while (i < cmd->cmdnbr)
			free(cmd->cmdpathlist[i++]);
		free(cmd->cmdpathlist);
	}
	i = 0;
	if (cmd->pipes)
	{
		while (i < cmd->cmdnbr - 1)
			free(cmd->pipes[i++]);
		free(cmd->pipes);
	}
}

void	closefd(t_cmd *cmd, int exitnbr, t_reader *reader)
{
	t_iteration	iter;

	iter.i = 0;
	while (iter.i < cmd->cmdnbr - 1)
	{
		close(cmd->pipes[iter.i][0]);
		close(cmd->pipes[iter.i][1]);
		iter.i++;
	}
	if (exitnbr > -1)
	{
		ft_cleanup_cmd(cmd);
		free(cmd);
		if (reader)
		{
			reader->commands = NULL;
			reader_free(reader);
		}
		exit(exitnbr);
	}
	if (reader)
		reader_free(reader);
}

int	ft_nbrofcmds(t_cmd *cmd)
{
	int	nbr;

	nbr = 0;
	while (cmd[nbr].args)
		nbr++;
	return (nbr);
}

static void ft_dispatch_builtin(t_cmd *cmd, t_list **tenvp, t_reader *exit)
{
    if (!ft_strncmp(cmd->args[0], "exit", 5))
        ft_exit(cmd->args, exit, NULL);
    else if (!ft_strncmp(cmd->args[0], "cd", 3))
        ft_cd(cmd->args, tenvp);
    else if (!ft_strncmp(cmd->args[0], "export", 7))
        ft_export(cmd->args, tenvp);
    else if (!ft_strncmp(cmd->args[0], "unset", 6))
        ft_unset(cmd->args, tenvp);
    else if (!ft_strncmp(cmd->args[0], "pwd", 4))
        ft_pwd(tenvp);
    else if (!ft_strncmp(cmd->args[0], "env", 4))
        ft_env(tenvp);
    else if (!ft_strncmp(cmd->args[0], "echo", 5))
        ft_echo(cmd->argc, cmd->args);
}

void    ft_exec_solobuiltin(t_cmd *cmd, t_list **tenvp, t_reader *exit)
{
    if (cmd->fd_infile != STDIN_FILENO)
    {
        cmd->stdin_backup = dup(STDIN_FILENO); 
        if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
            perror("dup2 infile");
    }
    if (cmd->fd_outfile != STDOUT_FILENO)
    {   
        cmd->stdout_backup = dup(STDOUT_FILENO); 
        if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
            perror("dup2 outfile");
    }
    ft_dispatch_builtin(cmd, tenvp, exit);
    if (cmd->stdin_backup != -1)
    {
        dup2(cmd->stdin_backup, STDIN_FILENO);
        close(cmd->stdin_backup);
    }
    if (cmd->stdout_backup != -1)
    {
        dup2(cmd->stdout_backup, STDOUT_FILENO);
        close(cmd->stdout_backup);
    }
}
