/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:31:44 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/06 14:50:06 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <errno.h>

/// Validates the provided command data based on its type.
/// @param type The type of the command to validate.
/// @param data The data associated with the command.
/// @return true if the command data is valid for the given type,
///         false otherwise.
bool	validate(t_command_type type, t_command_data data)
{
	if (type == COMMAND_COMMAND && data.command.name == NULL)
		return (false);
	if (type == COMMAND_BUILTIN && data.builtin.cmd == NULL)
		return (false);
	if ((type == COMMAND_REDIRECT_IN || type == COMMAND_REDIRECT_OUT
			|| type == COMMAND_REDIRECT_APPEND
			|| type == COMMAND_REDIRECT_HEREDOC) && data.redirect == NULL)
		return (false);
	if (type == COMMAND_PIPE && data.pipe == NULL)
		return (false);
	if (type == COMMAND_AND || type == COMMAND_OR)
		return (data.and_or != NULL);
	return (true);
}

t_cmd_token	*create_cmd_token(t_command_type type, t_command_data data)
{
	t_cmd_token	*token;

	token = ft_calloc(1, sizeof(t_cmd_token));
	if (token == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	if (!validate(type, data))
	{
		free(token);
		errno = EINVAL;
		return (NULL);
	}
	token->type = type;
	token->data = data;
	return (token);
}

t_parser	*parser_init(t_list *token_list)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	if (parser == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	parser->token_list = token_list;
	parser->len = ft_lstsize(token_list);
	return (parser);
}
