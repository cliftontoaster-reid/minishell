/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_none.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 12:00:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/// @brief Handles the initial state of the parser or when no specific
/// command/special token is being processed. It determines if the current token
/// is a command or a special token and transitions the parser state
/// accordingly.
/// @param parser The parser instance.
void	parser_handle_none(t_parser *parser)
{
	t_token_type	type;

	type = parser->current_token->type;
	if (type == TOKEN_WORD)
	{
		parser->state = PARSER_COMMAND;
		if (parser->command == NULL)
			parser->command = cmd_init();
		if (errno == ENOMEM)
			return ;
		ft_lstadd_back(&parser->argument_list,
			ft_lstnew(ft_strdup(parser->current_token->value)));
	}
	else if (type != TOKEN_NONE)
		parser->state = PARSER_SPECIAL;
	parser->current_index++;
}
