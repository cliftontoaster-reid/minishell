/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:34:25 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/16 14:45:46 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include <unistd.h>
#include "reader.h"

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
	if (reader)
		reader_free(reader);
	if (exitnbr > -1)
		exit(exitnbr);
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
