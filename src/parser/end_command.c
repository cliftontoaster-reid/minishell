/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:30:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 19:16:36 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shared.h"
#include <errno.h>
#include <stdlib.h>

bool	end_command_null_loop(t_parser *parser, int *idx, t_list *node)
{
	parser->command->args[*idx] = ft_strdup((char *)node->content);
	if (parser->command->args[*idx] == NULL)
	{
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
		return (true);
	}
	(*idx)++;
	node = node->next;
	return (false);
}

void	end_command_null(t_parser *parser)
{
	int		size;
	int		idx;
	t_list	*node;

	size = ft_lstsize(parser->argument_list);
	if (parser->command == NULL)
		parser->command = cmd_init();
	parser->command->args = ft_calloc(size + 1, sizeof(char *));
	if (parser->command->args == NULL)
	{
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
		return ;
	}
	idx = 0;
	node = parser->argument_list;
	while (node)
	{
		if (end_command_null_loop(parser, &idx, node))
			break ;
		node = node->next;
	}
	parser->command->args[idx] = NULL;
	parser->command->argc = size;
	ft_lstclear(&parser->argument_list, free);
}

void	end_command(t_parser *parser)
{
	if (parser->argument_list != NULL)
		end_command_null(parser);
	else
	{
		if (parser->command == NULL)
			parser->command = cmd_init();
		parser->command->args = ft_calloc(1, sizeof(char *));
		if (parser->command->args == NULL)
		{
			errno = ENOMEM;
			parser->error = PARSING_ERROR_MALLOC;
			return ;
		}
		parser->command->args[0] = NULL;
		parser->command->argc = 0;
	}
	ft_lstadd_back(&parser->command_list, ft_lstnew(parser->command));
	parser->command = NULL;
	parser->argument_list = NULL;
}
