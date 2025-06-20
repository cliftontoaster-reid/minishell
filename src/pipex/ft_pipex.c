/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:11:51 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/19 18:52:37 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //TODO
#include "shared.h"
#include "utils.h"

void	ft_pipex(t_cmd *cmd, t_list *tenvp)
{
	t_iteration	iter;

	printf("\n\n\n");

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
		printf("cmd->redirect_heredoc = %s\n",  cmd->redirect_heredoc);
	if (tenvp)
		printf("tenvp pwd = %s\n", b_getenv("PWD", tenvp));

	printf("\n\n\n");
}
