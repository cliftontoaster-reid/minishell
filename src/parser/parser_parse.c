/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:25:58 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 15:54:43 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "shared.h"
#include <errno.h>

// It should loop over all tokens in the lexer,
// -  when ecountering a word, it should take it as command name, and then
//   continue until it finds a token that is not a word or none.
// -  special tokens like redirections should be handled accordingly.

/// @brief Gets the nth element of a linked list.
/// @param lst The linked list.
/// @param n The index of the element to get.
/// @param size The total size of the list.
/// @return A pointer to the content of the nth element,
///          or NULL if not found or if arguments are invalid.
void	*ft_lstget(t_list *lst, size_t n, size_t size)
{
	size_t	i;

	if (!lst || n < 0)
		return (NULL);
	if (n >= size)
		return (NULL);
	i = 0;
	while (lst && i < n)
	{
		lst = lst->next;
		i++;
	}
	return (lst ? lst->content : NULL);
}

/// @brief Handles the initial state of the parser or when no specific command/special token is being processed.
/// It determines if the current token is a command or a special token and transitions the parser state accordingly.
/// @param parser The parser instance.
void	parser_handle_none(t_parser *parser)
{
	t_token_type	type;

	type = parser->current_token->type;
	if (type != TOKEN_NONE)
	{
		if (type == TOKEN_WORD)
		{
			parser->state = PARSER_COMMAND;
			ft_lstadd_back(&parser->command_list,
				ft_lstnew(ft_strdup(parser->current_token->value)));
		}
	}
	else
		parser->state = PARSER_SPECIAL;
	parser->current_index++;
}

/// @brief Handles the state when the parser is processing a command and its arguments.
/// It appends word tokens to the argument list. If a non-word token is encountered,
/// it transitions the parser state to handle special tokens.
/// @param parser The parser instance.
void	parser_handle_command(t_parser *parser)
{
	t_token_type	type;

	type = parser->current_token->type;
	if (type == TOKEN_NONE || type == TOKEN_WORD)
	{
		if (type == TOKEN_WORD)
			ft_lstadd_back(&parser->argument_list,
				ft_lstnew(ft_strdup(parser->current_token->value)));
	}
	else
		parser->state = PARSER_SPECIAL;
	parser->current_index++;
}

/// @brief Handles the pipe token when in the PARSER_SPECIAL state.
/// It checks for syntax errors (e.g., double pipes, pipe at the end of input)
/// and sets the is_pipe flag in the current command structure.
/// @param parser The parser instance.
static void	parser_special_pipe(t_parser *parser)
{
	t_token_type	type;
	t_token_type	next_type;
	t_token			*next_token;

	type = parser->current_token->type;
	next_token = (t_token *)ft_lstget(parser->token_list, parser->current_index
			+ 1, parser->token_count);
	if (!next_token)
	{
		errno = EINVAL;
		parser->error = PARSING_ERROR_MALLOC;
		return ;
	}
	next_type = next_token->type;
	if (type != TOKEN_NONE && next_type != TOKEN_WORD)
	{
		errno = EINVAL;
		parser->error = PARSING_DOUBLE_SPECIAL_DIRECTIVE;
		return ;
	}
	if (parser->command == NULL)
		parser->command = cmd_init();
	if (errno == ENOMEM)
		return ;
	parser->command->is_pipe = true;
}

/// @brief Retrieves the token that should be used as the target for a redirection.
/// This is typically the token immediately following a redirection operator.
/// It handles cases where the next token is a word or if there's a TOKEN_NONE in between.
/// Sets parser error if a valid target is not found.
/// @param parser The parser instance.
/// @return A pointer to the redirection target token,
///          or NULL if an error occurs or no valid token is found.
static inline t_token	*get_redirect_token(t_parser *parser)
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

/// @brief Handles the input redirection token ('<') when in the PARSER_SPECIAL state.
/// It retrieves the target filename for the redirection and stores it in the command structure.
/// Sets parser error on issues like missing target or memory allocation failure.
/// @param parser The parser instance.
static void	parser_special_redirect_in(t_parser *parser)
{
	t_token	*token;

	token = get_redirect_token(parser);
	if (!token)
		return ;
	if (parser->command == NULL)
		parser->command = cmd_init();
	if (errno == ENOMEM)
		return ;
	parser->command->redirect_in = ft_strdup(token->value);
	if (parser->command->redirect_in == NULL)
	{
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
	}
}

/// @brief Handles the output redirection token ('>') when in the PARSER_SPECIAL state.
/// It retrieves the target filename for the redirection and stores it in the command structure.
/// Sets parser error on issues like missing target or memory allocation failure.
/// @param parser The parser instance.
static void	parser_special_redirect_out(t_parser *parser)
{
	t_token	*token;

	token = get_redirect_token(parser);
	if (!token)
		return ;
	if (parser->command == NULL)
		///       will be set accordingly by that function.
		if (errno == ENOMEM)
			return ;
	parser->command->redirect_out = ft_strdup(token->value);
	if (parser->command->redirect_in == NULL)
	{
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
	}
}

/// @brief Handles the append output redirection token ('>>') when in the PARSER_SPECIAL state.
/// It retrieves the target filename for the redirection and stores it in the command structure.
/// Sets parser error on issues like missing target or memory allocation failure.
/// @param parser The parser instance.
static void	parser_special_redirect_append(t_parser *parser)
{
	t_token	*token;

	token = get_redirect_token(parser);
	if (!token)
		return ;
	if (parser->command == NULL)
		parser->command = cmd_init();
	if (errno == ENOMEM)
		return ;
	parser->command->redirect_append = ft_strdup(token->value);
	if (parser->command->redirect_in == NULL)
	{
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
	}
}

/// @brief Handles the here-document redirection token ('<<') when in the PARSER_SPECIAL state.
/// It retrieves the delimiter for the here-document and stores it in the command structure.
/// Sets parser error on issues like missing delimiter or memory allocation failure.
/// @param parser The parser instance.
static void	parser_special_redirect_heredoc(t_parser *parser)
{
	t_token	*token;

	token = get_redirect_token(parser);
	if (!token)
		return ;
	if (parser->command == NULL)
		parser->command = cmd_init();
	if (errno == ENOMEM)
		return ;
	parser->command->redirect_heredoc = ft_strdup(token->value);
	if (parser->command->redirect_in == NULL)
	{
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
	}
}

/// @brief Handles various special tokens (pipe,
///         redirections) based on the `last_token_type`.
/// It calls the appropriate specific handler for the encountered special token.
/// Sets parser error if an unexpected token sequence is found or if a required target for a special token is missing.
/// @param parser The parser instance.
void	parser_handle_special(t_parser *parser)
{
	t_token_type	type;

	type = parser->current_token->type;
	if (type != TOKEN_NONE && type != TOKEN_WORD)
	{
		errno = EINVAL;
		parser->error = PARSING_MISSING_SPECIAL_TARGET;
		return ;
	}
	switch (parser->last_token_type)
	{
	case TOKEN_PIPE:
		parser_special_pipe(parser);
		break ;
	case TOKEN_REDIRECT_IN:
		parser_special_redirect_in(parser);
		break ;
	case TOKEN_REDIRECT_OUT:
		parser_special_redirect_out(parser);
		break ;
	case TOKEN_REDIRECT_APPEND:
		parser_special_redirect_append(parser);
		break ;
	case TOKEN_REDIRECT_HEREDOC:
		parser_special_redirect_heredoc(parser);
		break ;
	default:
		errno = EINVAL;
		parser->error = PARSING_ERROR_MALLOC;
		return ;
	}
	parser->current_index++;
}

/// @brief Executes a single step in the parsing process based on the current parser state.
/// It calls the appropriate handler function (parser_handle_none,
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
	switch (parser->state)
	{
	case PARSER_NONE:
		parser_handle_none(parser);
		break ;
	case PARSER_COMMAND:
		parser_handle_command(parser);
		break ;
	case PARSER_SPECIAL:
		parser_handle_special(parser);
		break ;
	default:
		errno = EINVAL;
		return (PARSING_ERROR_MALLOC);
	}
	return (parser->error);
}

/// @brief Main parsing function that iterates through the token list and processes them.
/// It initializes the parser state and repeatedly calls `parser_step` to build the command structure.
/// It advances through the tokens and updates the parser's current and last token types.
/// @param parser The parser instance,
///                which contains the token list and other parsing state information.
/// @return A parsing error code, PARSING_NO_ERROR if parsing is successful,
///          or an error code if an issue occurred.
t_parsing_error	parser_parse(t_parser *parser)
{
	t_parsing_error	err;

	if (!parser || !parser->current_token || !parser->token_list)
	{
		errno = EINVAL;
		return (PARSING_ERROR_MALLOC);
	}
	parser->state = PARSER_NONE;
	err = PARSING_NO_ERROR;
	// Loop over tokens and parse them
	while (parser->current_index < parser->token_count)
	{
		parser_step(parser);
		// Move to the next token
		parser->current_token = ft_lstget(parser->token_list,
				parser->current_index, parser->token_count);
		if (!parser->current_token)
		{
			errno = EINVAL;
			return (PARSING_ERROR_MALLOC);
		}
		if (parser->error != PARSING_NO_ERROR)
			return (parser->error);
		parser->last_token_type = parser->current_token->type;
	}
	return (err);
}
