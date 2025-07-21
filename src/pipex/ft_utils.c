/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:34:25 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/21 13:23:14 by lfiorell@st      ###   ########.fr       */
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

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
