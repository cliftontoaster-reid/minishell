/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:25:58 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/24 16:40:25 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/// @brief Gets the nth element of a linked list.
/// @param lst The linked list.
/// @param n The index of the element to get.
/// @param size The total size of the list.
/// @return A pointer to the content of the nth element,
///          or NULL if not found or if arguments are invalid.
void	*ft_lstget(t_list *lst, size_t n, size_t size)
{
	size_t	i;

	if (!lst)
		return (NULL);
	if (n >= size)
		return (NULL);
	i = 0;
	while (lst && i < n)
	{
		lst = lst->next;
		i++;
	}
	if (lst == NULL)
		return (NULL);
	return (lst->content);
}

void	end_command(t_parser *parser)
{
	int		size;
	int		idx;
	t_list	*node;

	if (parser->argument_list != NULL)
	{
		// Build args array from argument_list
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
		// Copy arguments
		idx = 0;
		node = parser->argument_list;
		while (node)
		{
			parser->command->args[idx] = ft_strdup((char *)node->content);
			if (parser->command->args[idx] == NULL)
			{
				errno = ENOMEM;
				parser->error = PARSING_ERROR_MALLOC;
				return ;
			}
			idx++;
			node = node->next;
		}
		parser->command->args[idx] = NULL;
		parser->command->argc = size;
		ft_lstclear(&parser->argument_list, free);
	}
	ft_lstadd_back(&parser->command_list, ft_lstnew(parser->command));
	parser->command = NULL;
	parser->argument_list = NULL;
}

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
		// Add the command name to the argument list
		ft_lstadd_back(&parser->argument_list,
			ft_lstnew(ft_strdup(parser->current_token->value)));
	}
	else if (type != TOKEN_NONE)
		parser->state = PARSER_SPECIAL;
	parser->current_index++;
}

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

/// @brief Handles the pipe token when in the PARSER_SPECIAL state.
/// It checks for syntax errors (e.g., double pipes, pipe at the end of input)
/// and sets the is_pipe flag in the current command structure.
/// @param parser The parser instance.
static void	parser_special_pipe(t_parser *parser)
{
	if (parser->command == NULL)
		parser->command = cmd_init();
	parser->command->is_pipe = true;
	end_command(parser);
	parser->state = PARSER_NONE;
}

/// @brief Retrieves the token that should be used as the target for a
/// redirection. This is typically the token immediately following a redirection
/// operator. It handles cases where the next token is a word or if there's a
/// TOKEN_NONE in between. Sets parser error if a valid target is not found.
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

/// @brief Handles the input redirection token ('<') when in the PARSER_SPECIAL
/// state. It retrieves the target filename for the redirection and stores it in
/// the command structure. Sets parser error on issues like missing target or
/// memory allocation failure.
/// @param parser The parser instance.
static void	parser_special_redirect_in(t_parser *parser)
{
	t_token	*token;
	int		fd;

	token = get_redirect_token(parser);
	if (!token)
	{
		return ;
	}
	fd = open(token->value, O_RDONLY);
	if (fd < 0)
	{
		errno = EINVAL;
		parser->error = PARSING_MISSING_SPECIAL_TARGET;
		return ;
	}
	if (parser->command == NULL)
		parser->command = cmd_init();
	parser->command->fd_infile = fd;
	if (errno == ENOMEM)
		return ;
	parser->command->redirect_in = ft_strdup(token->value);
	if (parser->command->redirect_in == NULL)
	{
		close(fd);
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
	}
}

/// @brief Handles the output redirection token ('>') when in the PARSER_SPECIAL
/// state. It retrieves the target filename for the redirection and stores it in
/// the command structure. Sets parser error on issues like missing target or
/// memory allocation failure.
/// @param parser The parser instance.
static void	parser_special_redirect_out(t_parser *parser)
{
	t_token	*token;
	int		fd;

	token = get_redirect_token(parser);
	if (!token)
	{
		return ;
	}
	fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (parser->command == NULL)
		parser->command = cmd_init();
	if (fd < 0)
	{
		errno = EINVAL;
		parser->error = PARSING_MISSING_SPECIAL_TARGET;
		return ;
	}
	parser->command->fd_outfile = fd;
	if (errno == ENOMEM)
		return ;
	parser->command->redirect_out = ft_strdup(token->value);
	if (parser->command->redirect_out == NULL)
	{
		close(fd);
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
	}
}

/// @brief Handles the append output redirection token ('>>') when in the
/// PARSER_SPECIAL state. It retrieves the target filename for the redirection
/// and stores it in the command structure. Sets parser error on issues like
/// missing target or memory allocation failure.
/// @param parser The parser instance.
static void	parser_special_redirect_append(t_parser *parser)
{
	t_token	*token;
	int		fd;

	token = get_redirect_token(parser);
	if (!token)
	{
		return ;
	}
	fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		errno = EINVAL;
		parser->error = PARSING_MISSING_SPECIAL_TARGET;
		return ;
	}
	if (parser->command == NULL)
		parser->command = cmd_init();
	if (errno == ENOMEM)
		return ;
	parser->command->fd_outfile = fd;
	parser->command->redirect_append = ft_strdup(token->value);
	if (parser->command->redirect_in == NULL)
	{
		close(fd);
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
	}
}

/// @brief Handles the here-document redirection token ('<<') when in the
/// PARSER_SPECIAL state. It retrieves the delimiter for the here-document and
/// stores it in the command structure. Sets parser error on issues like missing
/// delimiter or memory allocation failure.
/// @param parser The parser instance.
static void	parser_special_redirect_heredoc(t_parser *parser)
{
	t_token	*token;

	token = get_redirect_token(parser);
	if (!token)
	{
		return ;
	}
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
/// Sets parser error if an unexpected token sequence is found or if a required
/// target for a special token is missing.
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
	t_parsing_error	err;

	if (!parser || !parser->token_list)
	{
		errno = EINVAL;
		return (PARSING_ERROR_MALLOC);
	}
	parser->state = PARSER_NONE;
	err = PARSING_NO_ERROR;
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
	if (parser->command != NULL || parser->argument_list != NULL)
		end_command(parser);
	return (err);
}
