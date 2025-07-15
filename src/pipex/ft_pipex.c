/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:03:33 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/15 15:24:30 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define _GNU_SOURCE
#include "pipex.h"
#include "shared.h"
#include "utils.h"
#include <sys/wait.h>

static void	pipe_redirection(t_cmd *cmd, int cmd_idx)
{
	if (cmd[cmd_idx].fd_infile != STDIN_FILENO)
		dup2(cmd[cmd_idx].fd_infile, STDIN_FILENO);
	else if (cmd_idx > 0)
		dup2(cmd->pipes[cmd_idx - 1][0], STDIN_FILENO);
	if (cmd[cmd_idx].fd_outfile != STDOUT_FILENO)
		dup2(cmd[cmd_idx].fd_outfile, STDOUT_FILENO);
	else if (cmd_idx < cmd->cmdnbr - 1)
		dup2(cmd->pipes[cmd_idx][1], STDOUT_FILENO);
	closefd(cmd, NO_EXIT);
}

static void	fd_child(t_cmd *cmd, t_list *tenvp, int cmd_idx)
{
	cmd[cmd_idx].pid = fork();
	if (cmd[cmd_idx].pid == -1)
	{
		printf("error fork of pid %d", cmd_idx);
		closefd(cmd, EXIT_FAILURE); // TODO handle exit failure
	}
	if (cmd[cmd_idx].pid == 0)
	{
		pipe_redirection(cmd, cmd_idx);
		is_builtin(cmd, &tenvp, cmd_idx);
		if (cmd->error == 1)
			closefd(cmd, EXIT_FAILURE); // TODO exit failure free
		/*
		   if (!cmd->cmdpathlist[cmd_idx])
		   closefd(cmd, EXIT_FAILURE); // TODO exit failure free
		 */
		execve(cmd->cmdpathlist[cmd_idx],
			cmd[cmd_idx].args,
			b_getenv(NULL, tenvp));
		// TODO handle exit failure
	}
}

void	ft_wait_for_children(void)
{
	int		status;
	int		sig;
	pid_t	wpid;

	wpid = waitpid(-1, &status, WNOHANG);
	while (wpid != -1)
	{
		if (wpid != 0)
		{
			if (WIFEXITED(status))
				g_status_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (WCOREDUMP(status))
					ft_putstr_fd(" (core dumped)", 2);
				ft_putstr_fd("\n", 2);
				g_status_code = 128 + sig;
			}
			else
				g_status_code = EXIT_FAILURE;
		}
		wpid = waitpid(-1, &status, WNOHANG);
	}
}

// iter.i, in fd_child indicates the command nbr
// waitpdid->(cmd[iter.i].pid, ...) and fd_child(cmd, tenvp, iter.i++) teamwork
static void	fd_pipex_execute(t_cmd *cmd, t_list *tenvp)
{
	t_iteration	iter;

	cmd->pipes = malloc(sizeof(int *) * (cmd->cmdnbr - 1));
	if (!cmd->pipes)
		return ;//TODO handle exit failure
	iter.i = 0;
	while (iter.i < cmd->cmdnbr - 1)
	{
		cmd->pipes[iter.i] = malloc(sizeof(int) * 2);
		if (pipe(cmd->pipes[iter.i++]) == -1)
			return ; //TODO handle exit failure
	}
	ft_cmdpathlist(cmd, tenvp);
	iter.i = 0;
	while (iter.i < cmd->cmdnbr)
		fd_child(cmd, tenvp, iter.i++);
	iter.i = 0;
	while (iter.i < cmd->cmdnbr - 1)
	{
		close(cmd->pipes[iter.i][0]);
		close(cmd->pipes[iter.i++][1]);
	}
	ft_wait_for_children();
}

// WARNING cmdpathlist does a malloc and contains mallocs
void	ft_pipex(t_cmd *cmd, t_list *tenvp)
{
	cmd->error = 0;
	cmd->cmdnbr = ft_nbrofcmds(cmd);
	if (!ft_strncmp(cmd->args[0], "exit", 5) && cmd->cmdnbr == 1)
		ft_exit(cmd->args, NULL);
	if (!ft_strncmp(cmd->args[0], "cd", 3) && cmd->cmdnbr == 1)
	{
		ft_cd(cmd->args, &tenvp);
		return ;
	}
	if (!ft_strncmp(cmd->args[0], "export", 7) && cmd->cmdnbr == 1)
	{
		ft_export(cmd->args, &tenvp);
		return ;
	}
	if (!ft_strncmp(cmd->args[0], "unset", 6) && cmd->cmdnbr == 1)
	{
		ft_unset(cmd->args, &tenvp);
		return ;
	}
	fd_pipex_execute(cmd, tenvp);
	if (cmd->error != 0)
		g_status_code = cmd->error; // TODO exit success free
}
