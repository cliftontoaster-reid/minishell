/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/22 13:33:49 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "reader.h"
#include "varextract.h"

bool	try_lex(t_reader *reader)
{
	reader->lexer = create_lexer(reader->cached);
	if (reader->lexer == NULL)
	{
		errno = ENOMEM;
		return (false);
	}
	reader->tokens = run_lexer(reader->lexer);
	if (reader->tokens == NULL && errno == EINVAL)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		free_lexer(reader->lexer);
		reader->lexer = NULL;
		g_status_code = 2;
		return (false);
	}
	if (reader->tokens == NULL)
	{
		free_lexer(reader->lexer);
		reader->lexer = NULL;
		errno = EINVAL;
		return (false);
	}
	reader->vars = b_varextract(reader->lexer->token_list);
	join_words(reader->lexer);
	return (true);
}
