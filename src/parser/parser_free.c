/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:35:34 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/15 14:33:47 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/// @brief Free a command structure and all its allocated memory
/// @param data Pointer to the command structure (cast to void*) to be freed
///
/// This function safely frees a t_cmd structure by:
/// - Freeing all argument strings in the args array
/// - Freeing the args array itself
/// - Freeing all redirection file paths
/// - Freeing the command structure itself
///
/// @note This function can safely handle NULL pointers
void	free_command(void *data)
{
	t_cmd	*command;

	command = (t_cmd *)data;
	if (command == NULL)
		return ;
	if (command->args != NULL)
	{
		while (command->argc > 0)
		{
			command->argc--;
			free(command->args[command->argc]);
		}
		free(command->args);
	}
	if (command->redirect_append != NULL)
		free(command->redirect_append);
	if (command->redirect_in != NULL)
		free(command->redirect_in);
	if (command->redirect_out != NULL)
		free(command->redirect_out);
	if (command->redirect_heredoc != NULL)
		free(command->redirect_heredoc);
	if (command->heredoc_delimiters != NULL)
		ft_lstclear(&command->heredoc_delimiters, free);
	free(command);
}

/// @brief Free a parser structure and all its allocated memory
/// @param parser Pointer to the parser structure to be freed
///
/// This function safely frees a t_parser structure by:
/// - Freeing the command list using the free_command function for each element
/// - Freeing the token list using the free_token function for each element
/// - Freeing the current command if it exists
/// - Freeing the parser structure itself
///
/// @note This function can safely handle NULL pointers
/// @note After freeing, the parser pointer is set to NULL (though this
///       only affects the local copy, not the original pointer)
void	parser_free(t_parser *parser)
{
	if (parser == NULL)
		return ;
	if (parser->command_list != NULL)
		ft_lstclear(&parser->command_list, free_command);
	if (parser->command != NULL)
		free_command(parser->command);
	free(parser);
	parser = NULL;
}
