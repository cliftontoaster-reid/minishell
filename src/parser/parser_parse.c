/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:25:58 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/18 13:58:47 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include "shared.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// It should loop over all tokens in the lexer,
// -  when ecountering a word, it should take it as command name, and then
//   continue until it finds a token that is not a word or none.
// -  special tokens like redirections should be handled accordingly.

/// @brief Handles various special tokens (pipe,
///         redirections) based on the `last_token_type`.
/// It calls the appropriate specific handler for the encountered special token.
/// Sets parser error if an unexpected token sequence is found or if a required
/// target for a special token is missing.
/// @param parser The parser instance.
void	parser_handle_special(t_parser *parser)
{
	if (parser->current_token->type != TOKEN_NONE
		&& parser->current_token->type != TOKEN_WORD)
	{
		if (parser->last_token_type != TOKEN_NONE
			&& parser->last_token_type != TOKEN_WORD)
		{
			errno = EINVAL;
			parser->error = PARSING_DOUBLE_SPECIAL_DIRECTIVE;
			return ;
		}
		errno = EINVAL;
		parser->error = PARSING_MISSING_SPECIAL_TARGET;
		return ;
	}
	if (parser->last_token_type == TOKEN_PIPE)
		parser_special_pipe(parser);
	else if (parser->last_token_type == TOKEN_REDIRECT_IN)
		parser_special_redirect_in(parser);
	else if (parser->last_token_type == TOKEN_REDIRECT_OUT)
		parser_special_redirect_out(parser);
	else if (parser->last_token_type == TOKEN_REDIRECT_APPEND)
		parser_special_redirect_append(parser);
	else if (parser->last_token_type == TOKEN_REDIRECT_HEREDOC)
		parser_special_redirect_heredoc(parser);
	else
	{
		errno = EINVAL;
		parser->error = PARSING_ERROR_MALLOC;
		return ;
	}
	parser->current_index++;
	parser->state = PARSER_NONE;
}

/// @brief Executes a single step in the parsing process based on the current
/// parser state. It calls the appropriate handler function (parser_handle_none,
///  parser_handle_command, or parser_handle_special).
/// @param parser The parser instance.
/// @return A parsing error code, PARSING_NO_ERROR if the step was successful,
///          or an error code if an issue occurred.
t_parsing_error	parser_step(t_parser *parser)
{
	if (!parser || !parser->current_token)
	{
		errno = EINVAL;
		return (PARSING_ERROR_MALLOC);
	}
	if (parser->state == PARSER_NONE)
		parser_handle_none(parser);
	else if (parser->state == PARSER_COMMAND)
		parser_handle_command(parser);
	else if (parser->state == PARSER_SPECIAL)
		parser_handle_special(parser);
	else
	{
		errno = EINVAL;
		return (PARSING_ERROR_MALLOC);
	}
	return (parser->error);
}

/// @brief Main parsing function that iterates through the token list and
/// processes them. It initializes the parser state and repeatedly calls
/// `parser_step` to build the command structure. It advances through the tokens
/// and updates the parser's current and last token types.
/// @param parser The parser instance,
///                which contains the token list and other parsing state
///                information.
/// @return A parsing error code, PARSING_NO_ERROR if parsing is successful,
///          or an error code if an issue occurred.
t_parsing_error	parser_parse(t_parser *parser)
{
	if (!parser || !parser->token_list)
	{
		errno = EINVAL;
		return (PARSING_ERROR_MALLOC);
	}
	parser->state = PARSER_NONE;
	parser->current_index = 0;
	while (parser->current_index < parser->token_count)
	{
		parser->current_token = ft_lstget(parser->token_list,
				parser->current_index, parser->token_count);
		if (!parser->current_token)
		{
			errno = EINVAL;
			return (PARSING_ERROR_MALLOC);
		}
		parser_step(parser);
		if (parser->error != PARSING_NO_ERROR)
			return (parser->error);
		parser->last_token_type = parser->current_token->type;
	}
	if (parser->state == PARSER_SPECIAL)
	{
		end_command(parser);
		return (PARSING_MISSING_SPECIAL_TARGET);
	}
	if (parser->command != NULL || parser->argument_list != NULL)
		end_command(parser);
	return (PARSING_NO_ERROR);
}
