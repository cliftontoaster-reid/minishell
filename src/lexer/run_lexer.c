/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:41:18 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 16:44:23 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <errno.h>

t_list	*run_lexer(t_lexer *lexer)
{
	if (lexer == NULL || lexer->text == NULL || lexer->text[0] == '\0')
		return (NULL);
	while (lexer->text[lexer->pos] != '\0')
	{
		if (lexer->state == LEXER_NONE)
			lexer_none(lexer);
		else if (lexer->state == LEXER_WORD)
			lexer_word(lexer);
		else if (lexer->state == LEXER_UNI)
			lexer_uni(lexer);
		else if (lexer->state == LEXER_DUO)
			lexer_duo(lexer);
		else
			lexer->pos++;
	}
	if (lexer->state == LEXER_WORD)
		end_token(lexer);
	if (lexer->state == LEXER_UNI || lexer->state == LEXER_DUO)
	{
		errno = EINVAL;
		return (NULL);
	}
	return (lexer->token_list);
}
