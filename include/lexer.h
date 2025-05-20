/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:52:34 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/20 11:14:11 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define SPECIAL_CHARS "|><"

/// @brief The different types of tokens that can be used in the lexer
typedef enum e_token_type
{
	/// @brief No token, should be ignored
	TOKEN_NONE = 0,
	/// @brief A command token, should be executed
	TOKEN_WORD,
	/// @brief A pipe token, should pass the output to the next command
	TOKEN_PIPE,
	/// @brief A redirect in token, should pass the input to the command
	TOKEN_REDIRECT_IN,
	/// @brief A redirect out token, should pass the output of the command
	TOKEN_REDIRECT_OUT,
	/// @brief A redirect append token, should append the output of the command
	TOKEN_REDIRECT_APPEND,
	/// @brief A redirect heredoc token, should pass the input to the command
	TOKEN_REDIRECT_HEREDOC,
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

/// @brief Create a new token
/// @param value The value of the token
/// @param type The type of the token
/// @return The new token
t_token				*create_token(char *value, t_token_type type);

/// @brief Free a token
/// @param token The token to free
void				free_token(t_token *token);

typedef enum e_lexer_state
{
	LEXER_NONE = 0,
	LEXER_WORD,
	LEXER_UNI,
	LEXER_DUO,
}					t_lexer_state;

typedef struct s_lexer
{
	char			*text;
	size_t			pos;
	char			current_char;

	t_lexer_state	state;
	size_t			start;

	t_list			*token_list;
}					t_lexer;

/// @brief Create a new lexer
/// @param text The text to lex
/// @return The new lexer
t_lexer				*create_lexer(char *text);

/// @brief Run the lexer
/// @param lexer The lexer to run
/// @return The list of tokens
t_list				*run_lexer(t_lexer *lexer);

/// @brief Free a lexer
/// @param lexer The lexer to free
void				free_lexer(t_lexer *lexer);

bool				end_token(t_lexer *lexer);

void				join_words(t_lexer *lexer);

#endif
