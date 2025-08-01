/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:03:33 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/28 10:58:15 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "libft.h"
#define MAX_PIPE_DEPTH 256
#include "pipex.h"
#include "reader.h"
#include "shared.h"
#include "utils.h"
#include <signal.h>
#include <sys/wait.h>

static int	pipe_redirection(t_cmd *cmd, int cmd_idx)
{
	if (cmd[cmd_idx].fd_infile != STDIN_FILENO)
		dup2(cmd[cmd_idx].fd_infile, STDIN_FILENO);
	else if (cmd_idx > 0)
		dup2(cmd->pipes[cmd_idx - 1][0], STDIN_FILENO);
	if (cmd[cmd_idx].fd_outfile != STDOUT_FILENO)
		dup2(cmd[cmd_idx].fd_outfile, STDOUT_FILENO);
	else if (cmd_idx < cmd->cmdnbr - 1)
		dup2(cmd->pipes[cmd_idx][1], STDOUT_FILENO);
	closefd(cmd, NO_EXIT, NULL);
	return (0);
}

static void	fd_child(t_cmd *cmd, t_list *tenvp, int cmd_idx, t_reader *exit)
{
	struct sigaction	sa;

	cmd[cmd_idx].pid = fork();
	if (cmd[cmd_idx].pid == -1)
	{
		printf("error fork of pid %d", cmd_idx);
		closefd(cmd, EXIT_FAILURE, exit);
	}
	if (cmd[cmd_idx].pid == 0)
	{
		sa.sa_handler = SIG_DFL;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0 + pipe_redirection(cmd, cmd_idx);
		sigaction(SIGPIPE, &sa, NULL);
		if (ft_check_if_builtin(cmd, cmd_idx))
			is_builtin(&cmd, &tenvp, cmd_idx, exit);
		if (cmd->error == 1)
			closefd(cmd, EXIT_FAILURE, exit);
		if (!cmd->cmdpathlist[cmd_idx])
			closefd(cmd, 127, exit);
		execve(cmd->cmdpathlist[cmd_idx], cmd[cmd_idx].args, b_getenv(NULL,
				tenvp));
		perror(cmd[cmd_idx].args[0]);
		closefd(cmd, EXIT_FAILURE, exit);
	}
}

void	ft_wait_for_children(int last_pid)
{
	int		status;
	int		sig;
	pid_t	wpid;

	wpid = waitpid(-1, &status, WNOHANG);
	while (wpid != -1)
	{
		if (wpid == last_pid)
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
// WARNING cmdpathlist does a malloc and contains mallocs
static void	fd_pipex_execute(t_cmd *cmd, t_list *tenvp, t_reader *exit)
{
	t_iteration	iter;

	cmd->pipes = malloc(sizeof(int *) * (cmd->cmdnbr - 1));
	if (!cmd->pipes)
		return ((void)cmd->error++);
	iter.i = 0;
	while (iter.i < cmd->cmdnbr - 1)
	{
		cmd->pipes[iter.i] = malloc(sizeof(int) * 2);
		if (pipe(cmd->pipes[iter.i++]) == -1)
			return ((void)cmd->error++);
	}
	ft_cmdpathlist(cmd, tenvp);
	iter.i = 0;
	while (iter.i < cmd->cmdnbr)
		fd_child(cmd, tenvp, iter.i++, exit);
	iter.i = 0;
	while (iter.i < cmd->cmdnbr - 1)
	{
		close(cmd->pipes[iter.i][0]);
		close(cmd->pipes[iter.i++][1]);
	}
	ft_wait_for_children(cmd[cmd->cmdnbr - 1].pid);
}

void	ft_pipex(t_cmd *cmd, t_list *tenvp, t_reader *exit)
{
	cmd->error = 0;
	cmd->cmdnbr = ft_nbrofcmds(cmd);
	cmd->stdin_backup = -1;
	cmd->stdout_backup = -1;
	if (cmd->cmdnbr > MAX_PIPE_DEPTH)
	{
		printf("max pipe reached. STOP, you're breaking the law.\n");
		return ;
	}
	else if (cmd->cmdnbr != 0)
	{
		if (cmd->cmdnbr == 1 && ft_check_if_builtin(cmd, 0))
			ft_exec_solobuiltin(cmd, &tenvp, exit);
		else
			fd_pipex_execute(cmd, tenvp, exit);
		if (cmd->error != 0)
			g_status_code = cmd->error;
	}
	ft_cleanup_cmd(cmd);
}
