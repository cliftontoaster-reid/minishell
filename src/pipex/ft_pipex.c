/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:11:51 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/27 18:57:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include <stdio.h> //TODO

static void	print_env_pwd(t_list *tenvp)
{
	char	**pwd_value;
	int		i;

	pwd_value = b_getenv("PWD", tenvp);
	if (pwd_value && pwd_value[0])
		printf("tenvp pwd = %s\n", pwd_value[0]);
	if (pwd_value)
	{
		i = 0;
		while (pwd_value[i])
			free(pwd_value[i++]);
		free(pwd_value);
	}
}

static void	handle_exit_command(t_cmd *cmd)
{
	int	exit_code;

	printf("Exiting...\n");
	if (cmd->args[1])
	{
		exit_code = atoi(cmd->args[1]);
		printf("Exit code: %d\n", exit_code);
		g_status_code = exit_code;
	}
	else
	{
		printf("No exit code provided, defaulting to 0.\n");
		g_status_code = 0;
	}
	exit(g_status_code);
}

static void	print_cmd_info(t_cmd *cmd)
{
	t_iteration	iter;

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
		print_cmd_info(cmd);
		if (tenvp)
			print_env_pwd(tenvp);
		if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
			handle_exit_command(cmd);
		cmd += 1;
	}
	printf("\n\n\n");
}
