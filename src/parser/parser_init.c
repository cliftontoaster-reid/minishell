/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:31:44 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/15 14:33:46 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <errno.h>
#include <unistd.h>

/// @brief Allocate and initialize a command structure.
/// @details Sets default values for arguments, redirections, and pipe flag.
/// @return Pointer to the initialized t_cmd structure,
///          or NULL on allocation failure (errno set to ENOMEM).
t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	cmd->args = NULL;
	cmd->argc = -1;
	cmd->fd_infile = STDIN_FILENO;
	cmd->fd_outfile = STDOUT_FILENO;
	cmd->is_pipe = false;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	cmd->redirect_append = NULL;
	cmd->redirect_heredoc = NULL;
	cmd->heredoc_delimiters = NULL;
	return (cmd);
}

/// @brief Allocate and initialize a parser structure.
/// @param token_list List of tokens to be parsed.
/// @return Pointer to the initialized t_parser structure,
///          or NULL on allocation failure (errno set to ENOMEM).
t_parser	*parser_init(t_list *token_list)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	if (parser == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	parser->token_list = token_list;
	parser->token_count = ft_lstsize(token_list);
	parser->argument_list = NULL;
	parser->command_list = NULL;
	parser->command = NULL;
	parser->current_token = NULL;
	parser->last_token_type = TOKEN_NONE;
	parser->current_index = 0;
	parser->state = PARSER_NONE;
	parser->error = PARSING_NO_ERROR;
	return (parser);
}
