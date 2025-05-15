/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:57:08 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/15 18:06:18 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	free_tok(void *token)
{
	free_token((t_token *)token);
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	if (lexer->text)
		free(lexer->text);
	if (lexer->token_list)
		ft_lstclear(&lexer->token_list, free_tok);
	free(lexer);
}
