/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:38:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/06 14:41:08 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "shared.h"

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

typedef enum e_parsing_error
{
	PARSING_NO_ERROR = 0,
	/// @brief Error while allocating memory
	PARSING_ERROR_MALLOC = 1,
	/// @brief Missing target for a redirect
	PARSING_MISSING_REDIRECT_IN = 2,
	/// @brief Missing target for a redirect
	PARSING_MISSING_REDIRECT_OUT = 3,
	/// @brief Missing target for a redirect
	PARSING_MISSING_REDIRECT_APPEND = 4,
	/// @brief Missing target for a redirect
	PARSING_MISSING_REDIRECT_HEREDOC = 5,
	/// @brief Missing target for a pipe
	PARSING_MISSING_PIPE_TARGET = 6,
}					t_parsing_error;

typedef enum e_parser_state
{
	PARSER_NONE = 0,
	PARSER_COMMAND,
	PARSER_ARG,
	PARSER_REDIRECT_IN,
	PARSER_REDIRECT_OUT,
	PARSER_REDIRECT_APPEND,
	PARSER_REDIRECT_HEREDOC,
}					t_parser_state;

typedef struct s_parser
{
	t_list			*command_list;
	t_command		*command;

	t_list			*token_list;
	t_token			*current_token;

	t_parser_state	state;
	size_t			pos;
	size_t			len;
}					t_parser;

/// @brief Initialize the parser
/// @param token_list The list of tokens to parse
/// @return A pointer to the parser
t_parser			*parser_init(t_list *token_list);

/// @brief Free the parser
/// @param parser The parser to free
void				parser_free(t_parser *parser);

/// @brief Parse the tokens
/// @param parser The parser to use
/// @return The parsing error
t_parsing_error		parser_parse(t_parser *parser);

/// @brief Turns the AST into a list of commands
/// @param parser The parser to use
/// @return A list of commands
t_cmd_token			*parser_to_list(t_parser *parser);
