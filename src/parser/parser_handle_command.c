/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 12:00:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/// @brief Handles the state when the parser is processing a command and its
/// arguments. It appends word tokens to the argument list. If a non-word token
/// is encountered, it transitions the parser state to handle special tokens.
/// @param parser The parser instance.
void	parser_handle_command(t_parser *parser)
{
	t_token_type	type;

	type = parser->current_token->type;
	if (type == TOKEN_WORD)
	{
		ft_lstadd_back(&parser->argument_list,
			ft_lstnew(ft_strdup(parser->current_token->value)));
	}
	else if (type != TOKEN_NONE)
		parser->state = PARSER_SPECIAL;
	parser->current_index++;
}
