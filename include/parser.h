/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:38:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/23 10:50:32 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "libft.h"
# include "shared.h"

typedef struct s_cmd t_cmd;
typedef struct s_reader t_reader;

/// - bit 0 : command is a builtin
///
/// - bit 1 : has input redirection
///
/// - bit 2 : has output redirection
///
/// - bit 3 : has error redirection
///
/// - bit 4 : has pipe in
///
/// - bit 5 : has pipe out
///
/// - bit 6 : soft redirect
///
/// - bit 7 : is local

/// @brief Defines the possible parsing errors that can occur.
typedef enum e_parsing_error
{
	PARSING_NO_ERROR = 0,
	/// @brief Error while allocating memory
	PARSING_ERROR_MALLOC = 1,
	/// @brief Missing target for a special token
	PARSING_MISSING_SPECIAL_TARGET = 2,
	/// @brief Double special directive
	PARSING_DOUBLE_SPECIAL_DIRECTIVE = 3,
}					t_parsing_error;

/// @brief Represents the current state of the parser.
typedef enum e_parser_state
{
	/// @brief The parser is in an initial or undefined state.
	PARSER_NONE = 0,
	/// @brief The parser is currently processing a command.
	PARSER_COMMAND,
	/// @brief The parser is currently processing a special token (e.g., pipe,
	///         redirection).
	PARSER_SPECIAL,
}					t_parser_state;

/// @brief Represents the parser's state and data structures.
typedef struct s_parser
{
	/// @brief A linked list of commands that have been parsed.
	t_list			*command_list;
	/// @brief The command currently being built.
	t_cmd			*command;
	/// @brief A linked list of arguments for the current command.
	t_list			*argument_list;

	/// @brief The original list of tokens from the lexer.
	t_list			*token_list;
	/// @brief The token currently being processed.
	t_token			*current_token;
	/// @brief The type of the last token that was processed.
	t_token_type	last_token_type;

	/// @brief The index of the current token in the token list.
	size_t			current_index;
	/// @brief The total number of tokens to be parsed.
	size_t			token_count;

	/// @brief The current state of the parser.
	t_parser_state	state;

	/// @brief The last error that occurred during parsing, if any.
	t_parsing_error	error;
}					t_parser;

/// @brief Initialize the parser
/// @param token_list The list of tokens to parse
/// @return A pointer to the parser
t_parser			*parser_init(t_list *token_list);

/// @brief Free the parser
/// @param parser The parser to free
void				parser_free(t_parser *parser);

/// @brief Free a command
/// @param data The command to free
void				free_command(void *data);

/// @brief Parse the tokens
/// @param parser The parser to use
/// @return The parsing error
t_parsing_error		parser_parse(t_parser *parser);

/// @brief Gets the nth element of a linked list.
/// @param lst The linked list.
/// @param n The index of the element to get.
/// @param size The total size of the list.
/// @return A pointer to the content of the nth element,
///          or NULL if not found or if arguments are invalid.
void				*ft_lstget(t_list *lst, size_t n, size_t size);

/// @brief Handles the initial state of the parser or when no specific command/special token is being processed.
/// It determines if the current token is a command or a special token and transitions the parser state accordingly.
/// @param parser The parser instance.
void				parser_handle_none(t_parser *parser);

/// @brief Handles the state when the parser is processing a command and its arguments.
/// It appends word tokens to the argument list. If a non-word token is encountered,
/// it transitions the parser state to handle special tokens.
/// @param parser The parser instance.
void				parser_handle_command(t_parser *parser);

/// @brief Handles various special tokens (pipe,
///         redirections) based on the `last_token_type`.
/// It calls the appropriate specific handler for the encountered special token.
/// Sets parser error if an unexpected token sequence is found or if a required target for a special token is missing.
/// @param parser The parser instance.
void				parser_handle_special(t_parser *parser);

/// @brief Executes a single step in the parsing process based on the current parser state.
///  It calls the appropriate handler function (parser_handle_none,
///  parser_handle_command, or parser_handle_special).
/// @param parser The parser instance.
/// @return A parsing error code, PARSING_NO_ERROR if the step was successful,
///          or an error code if an issue occurred.
t_parsing_error		parser_step(t_parser *parser);

/// @brief Turns the AST into a list of commands
/// @param parser The parser to use
/// @return A list of commands
t_cmd				*parser_to_list(t_parser *parser);

/// @brief Allocate and initialize a command structure.
/// @details Sets default values for arguments, redirections, and pipe flag.
/// @return Pointer to the initialized t_cmd structure,
///          or NULL on allocation failure (errno set to ENOMEM).
t_cmd				*cmd_init(void);

char				*p_strerror(t_parsing_error error);

#endif
