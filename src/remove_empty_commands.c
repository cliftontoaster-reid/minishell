/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:37:49 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 19:38:44 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_cmd	*copy_valid_commands(t_cmd *commands, t_cmd *new_commands, size_t count,
		size_t valid_count)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (i < count)
	{
		if (commands[i].argc > 0)
			new_commands[j++] = commands[i];
		i++;
	}
	ft_bzero(&new_commands[valid_count], sizeof(t_cmd));
	new_commands[valid_count].argc = -1;
	free(commands);
	return (new_commands);
}

t_cmd	*remove_empty_commands(t_cmd *commands)
{
	size_t	count;
	size_t	valid_count;
	t_cmd	*new_commands;

	if (!commands)
		return (NULL);
	count = 0;
	valid_count = 0;
	while (commands[count].args)
	{
		if (commands[count++].argc > 0)
			valid_count++;
	}
	new_commands = ft_calloc(valid_count + 1, sizeof(t_cmd));
	if (!new_commands)
		return (NULL);
	return (copy_valid_commands(commands, new_commands, count, valid_count));
}
