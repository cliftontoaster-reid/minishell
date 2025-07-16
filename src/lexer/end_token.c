/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:40:56 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 16:50:51 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <errno.h>

/// @brief Finalize the current token in the lexer and append it to its
///        token list
/// @param lexer Pointer to the lexer containing the current state, input text,
///              and token list
///
/// If the lexer is not in a token-building state (LEXER_NONE),
///	this function does nothing
/// and returns true. Otherwise, it:
///
///   1. Extracts the substring from lexer->text spanning [lexer->start,
///      lexer->pos).
///
///   2. Creates a new TOKEN_WORD token with that substring.
///
///   3. Wraps the token in a list node and appends it to lexer->token_list.
///
///   4. Resets lexer->state to LEXER_NONE.
///
/// On any allocation or creation failure, it releases allocated resources
/// and returns false.
///
/// @return (true on successful token finalization and addition); false on error
bool	end_token(t_lexer *lexer)
{
	char			*value;
	t_token			*token;
	t_list			*new_node;
	t_token_type	type;

	if (lexer->state == LEXER_NONE)
		type = TOKEN_NONE;
	else
		type = TOKEN_WORD;
	value = ft_substr(lexer->text, lexer->start, lexer->pos - lexer->start);
	if (value == NULL)
	{
		errno = ENOMEM;
		return (false);
	}
	token = create_token(value, type);
	free(value);
	if (token == NULL)
	{
		errno = ENOMEM;
		return (false);
	}
	new_node = ft_lstnew(token);
	if (new_node == NULL)
	{
		free_token(token);
		errno = ENOMEM;
		return (false);
	}
	ft_lstadd_back(&lexer->token_list, new_node);
	lexer->state = LEXER_NONE;
	lexer->start = lexer->pos;
	return (true);
}
