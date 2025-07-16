/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_duo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:41:27 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 16:45:29 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_duo(t_lexer *lexer)
{
	if (lexer->text[lexer->pos] == '"')
	{
		end_token(lexer);
		lexer->state = LEXER_NONE;
		lexer->start = lexer->pos + 1;
	}
	lexer->pos++;
}
