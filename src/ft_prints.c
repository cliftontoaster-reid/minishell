/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:30:00 by lfiorell@st      #+#    #+#             */
/*   Updated: 2025/07/16 20:30:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_extra.h"
#include "shared.h"
#include <stdio.h>

void	ft_prints(t_cmd *cmd)
{
	printf("Command: %s, Arg Count: %d", cmd->args[0], cmd->argc);
	if (cmd->is_pipe)
		printf(" (Pipe)");
	if (cmd->fd_infile != -1)
		printf(", Infile: %d", cmd->fd_infile);
	if (cmd->fd_outfile != -1)
		printf(", Outfile: %d", cmd->fd_outfile);
	if (cmd->redirect_in)
		printf(", Redirect In: %s", cmd->redirect_in);
	if (cmd->redirect_out)
		printf(", Redirect Out: %s", cmd->redirect_out);
	if (cmd->redirect_append)
		printf(", Redirect Append: %s", cmd->redirect_append);
	if (cmd->redirect_heredoc)
		printf(", Redirect Heredoc: %s", cmd->redirect_heredoc);
	printf("\n");
}
