/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_redirect_heredoc.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:43:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/18 13:46:30 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shared.h"
#include <errno.h>
#include <stdlib.h>

/// @brief Handles the here-document redirection token ('<<') when in the
/// PARSER_SPECIAL state. It retrieves the delimiter for the here-document and
/// stores it in the command structure. Sets parser error on issues like missing
/// delimiter or memory allocation failure. If there's already a heredoc
/// redirection,
/// it frees the previous delimiter and replaces it with the new one.
/// @param parser The parser instance.
void	parser_special_redirect_heredoc(t_parser *parser)
{
	t_token	*token;

	token = get_redirect_token(parser);
	if (!token)
	{
		parser->error = PARSING_MISSING_SPECIAL_TARGET;
		return ;
	}
	if (parser->command == NULL)
		parser->command = cmd_init();
	if (parser->command->heredoc_delimiters == NULL)
		parser->command->heredoc_delimiters = NULL;
	ft_lstadd_back(&parser->command->heredoc_delimiters,
		ft_lstnew(ft_strdup(token->value)));
	if (parser->command->redirect_heredoc != NULL)
		free(parser->command->redirect_heredoc);
	parser->command->redirect_heredoc = ft_strdup(token->value);
	if (parser->command->redirect_heredoc == NULL)
	{
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
	}
}
