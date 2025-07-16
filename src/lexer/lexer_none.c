/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_none.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:44:09 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 16:45:26 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/// @brief Handle the default lexer state when no token is in progress.
///
/// This function examines the character at lexer->pos in the input text
/// and takes one of the following actions:
///
///   - If it's whitespace, simply advance the position.
///
///   - If it's a double-quote or single-quote, switch to QUOTE states
///     (`LEXER_DUO` or `LEXER_UNI`) and mark the start of the quoted token.
///
///   - If it's a special character (|, >, >>, <, <<), create the
///     corresponding pipe or redirection token, append it to the token
///     list, and adjust for two-character operators.
///
///   - Otherwise, begin a new WORD token by switching to LEXER_WORD and
///     marking the start position.
///
/// After processing, always advance lexer->pos by one (or two for
/// >> and <<) to continue scanning.
///
/// @param lexer Pointer to the lexer structure
void	lexer_none(t_lexer *lexer)
{
	if (!ft_ciswhite(lexer->text[lexer->pos]))
	{
		end_token(lexer);
		if (lexer->text[lexer->pos] == '"')
		{
			lexer->state = LEXER_DUO;
			lexer->start = lexer->pos + 1;
		}
		else if (lexer->text[lexer->pos] == '\'')
		{
			lexer->state = LEXER_UNI;
			lexer->start = lexer->pos + 1;
		}
		else if (ft_strchr(SPECIAL_CHARS, lexer->text[lexer->pos]))
			lexer_special(lexer);
		else
		{
			lexer->state = LEXER_WORD;
			lexer->start = lexer->pos;
		}
	}
	lexer->pos++;
}
