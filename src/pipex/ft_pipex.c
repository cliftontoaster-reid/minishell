/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:03:33 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/04 14:52:49 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "pipex.h"

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
		if (cmd->error == 1)
			closefd(cmd, EXIT_FAILURE); // TODO exit failure free
		/*
		if (!cmd->cmdpathlist[cmd_idx])
			return (closefd(cmd, exit)); // TODO handle exit failure
		*/
		if (cmd[cmd_idx].fd_infile != STDIN_FILENO)
			dup2(cmd[cmd_idx].fd_infile, STDIN_FILENO);
		else if (cmd_idx > 0)
			dup2(cmd->pipes[cmd_idx - 1][0], STDIN_FILENO);
		if (cmd[cmd_idx].fd_outfile != STDOUT_FILENO)
			dup2(cmd[cmd_idx].fd_outfile, STDOUT_FILENO);
		else if (cmd_idx < cmd->cmdnbr - 1)
			dup2(cmd->pipes[cmd_idx][1], STDOUT_FILENO);
		closefd(cmd, 0);
		execve(cmd->cmdpathlist[cmd_idx], cmd[cmd_idx].args, b_getenv(NULL, tenvp));
		// TODO handle exit failure
	}
}

//iter.i, in fd_child indicates the command nbr
//waitpdid->(cmd[iter.i].pid, ...) and fd_child(cmd, tenvp, iter.i++) teamwork
static void	fd_pipex_execute(t_cmd *cmd, t_list *tenvp)
{
	t_iteration iter;

	cmd->pipes = malloc(sizeof(int *) * (cmd->cmdnbr - 1));
	if (!cmd->pipes)
		return ; // TODO handle exit failure
	iter.i = 0;
	while (iter.i < cmd->cmdnbr - 1)
	{
		cmd->pipes[iter.i] = malloc(sizeof(int) * 2);
		if (pipe(cmd->pipes[iter.i++]) == -1)
			return ; // TODO handle exit failure
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
	iter.i = 0;
	while (iter.i < cmd->cmdnbr)
		if (waitpid(cmd[iter.i++].pid, NULL, 0) == -1)
			return ; // TODO handle exit failure
}

//WARNING cmdpathlist does a malloc and contains mallocs
void	ft_pipex(t_cmd *cmd, t_list *tenvp)
{
	cmd->error = 0;
	cmd->cmdnbr = ft_nbrofcmds(cmd);
	if (!ft_strncmp(cmd->args[0], "exit", 4) && cmd->cmdnbr == 1)
		ft_exit(cmd->args, NULL);
	fd_pipex_execute(cmd, tenvp);
	g_status_code = cmd->error; // TODO exit success free
}

/*
void	ft_pipex(t_cmd *cmd, t_list *tenvp)
{
	t_iteration	iter;
	//int			exit_code;

	iter.i = 0;
	while (cmd->args[iter.i])
	{
		printf("cmd->arg %d = %s\n", iter.i, cmd->args[iter.i]);
		iter.i++;
	}
	if (cmd->argc)
		printf("cmd->argc = %d\n", cmd->argc);
	if (cmd->fd_infile)
		printf("cmd->fd_infile = %d\n", cmd->fd_infile);
	if (cmd->fd_outfile)
		printf("cmd->fd_outfile = %d\n", cmd->fd_outfile);
	if (cmd->redirect_in)
		printf("cmd->redirect_in = %s\n", cmd->redirect_in);
	if (cmd->redirect_out)
		printf("cmd->redirect_out = %s\n", cmd->redirect_out);
	if (cmd->redirect_append)
		printf("cmd->redirect_append = %s\n", cmd->redirect_append);
	if (cmd->redirect_heredoc)
		printf("cmd->redirect_heredoc = %s\n", cmd->redirect_heredoc);
}

void	ft_pipex(t_cmd *cmd, t_list *tenvp)
{
	printf("\n\n\n");
	while (cmd && cmd->args)
	{
		iter.i = 0;
		while (cmd->args[iter.i])
		{
			printf("cmd->arg[%d] = %s\n", iter.i, cmd->args[iter.i]);
			iter.i++;
		}
		if (cmd->argc)
			printf("cmd->argc = %d\n", cmd->argc);
		if (cmd->fd_infile >= 0)
			printf("cmd->fd_infile = %d\n", cmd->fd_infile);
		if (cmd->fd_outfile)
			printf("cmd->fd_outfile = %d\n", cmd->fd_outfile);
		if (cmd->redirect_in)
			printf("cmd->redirect_in = %s\n", cmd->redirect_in);
		if (cmd->redirect_out)
			printf("cmd->redirect_out = %s\n", cmd->redirect_out);
		if (cmd->redirect_append)
			printf("cmd->redirect_append = %s\n", cmd->redirect_append);
		if (cmd->redirect_heredoc)
			printf("cmd->redirect_heredoc = %s\n", cmd->redirect_heredoc);
		if (tenvp)
			printf("tenvp pwd = %s\n", b_getenv("PATH", tenvp));
		printf("bool is : %d\n", cmd->is_pipe);
		printf("\n");
		cmd += 1;
	}
	printf("\n\n");
}
*/
