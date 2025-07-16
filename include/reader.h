/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:43:50 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:23:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "shared.h"
# include "utils.h"
# include <errno.h>
# include <stdio.h>

typedef struct s_parser	t_parser;
typedef struct s_cmd	t_cmd;

typedef enum e_reader_state
{
	READING,
	LEXING,
	PARSING,
	EXECUTING,
}						t_reader_state;

typedef struct s_reader
{
	char				*cached;
	t_lexer				*lexer;
	t_list				*tokens;
	t_parser			*parser;
	t_list				*env;
	t_list				*vars;
	int					*pids;
	t_reader_state		state;
	char				*cached_input;
	t_linereader		*linereader;
	t_cmd				*commands;
	char				**varnames;
}						t_reader;

t_reader				*reader_init(char *const *envp);

void					reader_free(t_reader *reader);

void					handle_read(t_reader *reader, const char *input);

bool					try_read(t_reader *reader, const char *input);

bool					try_lex(t_reader *reader);

bool					try_parse(t_reader *reader);

bool					str_is_whitespace(const char *str);

bool					handle_read_two(t_reader *reader);

#endif
