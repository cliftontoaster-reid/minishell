/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:31:08 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/06 14:50:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "lexer.h"

t_lexer	*create_lexer(char *text)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
	{
		errno = ENOMEM;
		return (NULL);
	}
	lexer->text = ft_strdup(text);
	if (!lexer->text)
	{
		free(lexer);
		errno = ENOMEM;
		return (NULL);
	}
	lexer->pos = 0;
	lexer->current_char = lexer->text[0];
	lexer->state = LEXER_NONE;
	return (lexer);
}
