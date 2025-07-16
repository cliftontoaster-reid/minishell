/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:43:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 16:43:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_word(t_lexer *lexer)
{
	if (ft_ciswhite(lexer->text[lexer->pos]))
	{
		end_token(lexer);
		lexer->start = lexer->pos;
	}
	else if (ft_strchr(SPECIAL_CHARS, lexer->text[lexer->pos]))
	{
		end_token(lexer);
		lexer_special(lexer);
	}
	else if (lexer->text[lexer->pos] == '"')
	{
		end_token(lexer);
		lexer->state = LEXER_DUO;
		lexer->start = lexer->pos + 1;
	}
	else if (lexer->text[lexer->pos] == '\'')
	{
		end_token(lexer);
		lexer->state = LEXER_UNI;
		lexer->start = lexer->pos + 1;
	}
	lexer->pos++;
}
