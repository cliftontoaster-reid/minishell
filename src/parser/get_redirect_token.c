/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:40:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 18:59:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shared.h"
#include <errno.h>

/// @brief Retrieves the token that should be used as the target for a
/// redirection. This is typically the token immediately following a redirection
/// operator. It handles cases where the next token is a word or if there's a
/// TOKEN_NONE in between. Sets parser error if a valid target is not found.
/// @param parser The parser instance.
/// @return A pointer to the redirection target token,
///          or NULL if an error occurs or no valid token is found.
t_token	*get_redirect_token(t_parser *parser)
{
	t_token	*token;

	token = NULL;
	if (parser->current_token->type == TOKEN_WORD)
	{
		token = parser->current_token;
	}
	else if (parser->current_token->type == TOKEN_NONE
		&& (t_token *)ft_lstget(parser->token_list, parser->current_index++,
			parser->token_count))
	{
		token = (t_token *)ft_lstget(parser->token_list, parser->current_index,
				parser->token_count);
	}
	else
	{
		errno = EINVAL;
		parser->error = PARSING_MISSING_SPECIAL_TARGET;
	}
	return (token);
}
