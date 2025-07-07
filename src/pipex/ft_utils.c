/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:34:25 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/07 14:23:55 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "pipex.h"

void	closefd(t_cmd *cmd, int exitnbr)
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
		exit(exitnbr);
}

int		ft_nbrofcmds(t_cmd *cmd)
{
	int nbr;

	nbr = 0;
	while (cmd[nbr].args)
		nbr++;
	return (nbr);
}
