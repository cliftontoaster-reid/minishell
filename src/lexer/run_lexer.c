/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:41:18 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/15 14:44:21 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
		return (false);
	token = create_token(value, type);
	free(value);
	if (token == NULL)
		return (false);
	new_node = ft_lstnew(token);
	if (new_node == NULL)
	{
		free_token(token);
		return (false);
	}
	ft_lstadd_back(&lexer->token_list, new_node);
	lexer->state = LEXER_NONE;
	return (true);
}

void	lexer_special(t_lexer *lexer)
{
	t_token			*token;
	t_list			*new_node;
	t_token_type	type;
	bool			special;

	special = false;
	if (lexer->text[lexer->pos] == '|')
		type = TOKEN_PIPE;
	else
	{
		if (lexer->text[lexer->pos] == '>')
		{
			if (lexer->text[lexer->pos + 1] == '>')
			{
				type = TOKEN_REDIRECT_APPEND;
				special = true;
			}
			else
				type = TOKEN_REDIRECT_OUT;
		}
		else if (lexer->text[lexer->pos] == '<')
		{
			if (lexer->text[lexer->pos + 1] == '<')
			{
				type = TOKEN_REDIRECT_HEREDOC;
				special = true;
			}
			else
				type = TOKEN_REDIRECT_IN;
		}
	}
	token = create_token(ft_substr(lexer->text, lexer->pos, 1 + special), type);
	if (token == NULL)
		return ;
	new_node = ft_lstnew(token);
	if (new_node == NULL)
	{
		free_token(token);
		return ;
	}
	ft_lstadd_back(&lexer->token_list, new_node);
	if (special)
		lexer->pos++;
}

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
	t_token_type	type;

	type = TOKEN_NONE;
	if (!ft_ciswhite(lexer->text[lexer->pos]))
	{
		end_token(lexer);
		if (lexer->text[lexer->pos] == '"')
		{
			lexer->state = LEXER_DUO;
			lexer->start = lexer->pos;
		}
		else if (lexer->text[lexer->pos] == '\'')
		{
			lexer->state = LEXER_UNI;
			lexer->start = lexer->pos;
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

void	lexer_word(t_lexer *lexer)
{
	t_token_type	type;

	type = TOKEN_NONE;
	if (ft_ciswhite(lexer->text[lexer->pos]))
		end_token(lexer);
	else if (ft_strchr(SPECIAL_CHARS, lexer->text[lexer->pos]))
	{
		end_token(lexer);
		lexer_special(lexer);
	}
	else if (lexer->text[lexer->pos] == '"')
	{
		end_token(lexer);
		lexer->state = LEXER_DUO;
		lexer->start = lexer->pos;
	}
	else if (lexer->text[lexer->pos] == '\'')
	{
		end_token(lexer);
		lexer->state = LEXER_UNI;
		lexer->start = lexer->pos;
	}
	else
	{
		if (end_token(lexer) == false)
			return ;
	}
	lexer->pos++;
}

void	lexer_uni(t_lexer *lexer)
{
	if (lexer->text[lexer->pos] == '\'')
	{
		end_token(lexer);
		lexer->state = LEXER_NONE;
	}
	lexer->pos++;
}

void	lexer_duo(t_lexer *lexer)
{
	if (lexer->text[lexer->pos] == '"')
	{
		end_token(lexer);
		lexer->state = LEXER_NONE;
	}
	lexer->pos++;
}

t_list	*run_lexer(t_lexer *lexer)
{
	if (lexer == NULL || lexer->text == NULL)
		return (NULL);
	while (lexer->text[lexer->pos] != '\0')
	{
		if (lexer->state == LEXER_NONE)
			lexer_none(lexer);
		else if (lexer->state == LEXER_WORD)
			lexer_word(lexer);
		else if (lexer->state == LEXER_UNI)
			lexer_uni(lexer);
		else if (lexer->state == LEXER_DUO)
			lexer_duo(lexer);
		else
			lexer->pos++;
		if (lexer->text[lexer->pos] == '\0')
		{
			if (lexer->state != LEXER_NONE || lexer->state != LEXER_WORD)
				return (NULL);
			end_token(lexer);
			break ;
		}
	}
	return (lexer->token_list);
}
