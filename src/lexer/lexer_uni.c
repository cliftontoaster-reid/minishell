/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_uni.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:43:28 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 18:07:08 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_uni(t_lexer *lexer)
{
	if (lexer->text[lexer->pos] == '\'')
	{
		end_token(lexer);
		lexer->state = LEXER_NONE;
		lexer->start = lexer->pos + 1;
	}
	if (lexer->text[lexer->pos] == '$')
		lexer->text[lexer->pos] = '\x80';
	lexer->pos++;
}
