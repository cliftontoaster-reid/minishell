/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:38:30 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/19 15:40:55 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <errno.h>

t_cmd	*parser_to_list(t_parser *parser)
{
	size_t	len;
	size_t	i;
	t_cmd	*commands;
	t_list	*current;

	if (parser == NULL || parser->command_list == NULL)
	{
		errno = EINVAL;
		return (NULL);
	}
	len = ft_lstsize(parser->command_list);
	if (len == 0)
	{
		errno = EINVAL;
		return (NULL);
	}
	commands = ft_calloc(len, sizeof(t_cmd));
	if (commands == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	current = parser->command_list;
	while (current && i < len)
	{
		commands[i] = *(t_cmd *)current->content;
		current = current->next;
		i++;
	}
	if (i < len)
	{
		free(commands);
		errno = EINVAL;
		return (NULL);
	}
	return (commands);
}
