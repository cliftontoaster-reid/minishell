/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_redirect_out.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:41:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 19:02:02 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shared.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	parser_special_redirect_out_more(t_parser *parser, t_token *token,
		int fd)
{
	if (parser->command->fd_outfile > STDOUT_FILENO)
		close(parser->command->fd_outfile);
	parser->command->fd_outfile = fd;
	if (errno == ENOMEM)
		return ;
	if (parser->command->redirect_out != NULL)
		free(parser->command->redirect_out);
	parser->command->redirect_out = ft_strdup(token->value);
	if (parser->command->redirect_out == NULL)
	{
		close(fd);
		errno = ENOMEM;
		parser->error = PARSING_ERROR_MALLOC;
	}
}

/// @brief Handles the output redirection token ('>') when in the PARSER_SPECIAL
/// state. It retrieves the target filename for the redirection and stores it in
/// the command structure. Sets parser error on issues like missing target or
/// memory allocation failure. If there's already an output redirection,
/// it closes the previous file descriptor and replaces it with the new one.
/// @param parser The parser instance.
void	parser_special_redirect_out(t_parser *parser)
{
	t_token	*token;
	int		fd;

	token = get_redirect_token(parser);
	if (!token)
	{
		return ;
	}
	fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (parser->command == NULL)
		parser->command = cmd_init();
	if (fd < 0)
	{
		errno = EINVAL;
		parser->error = PARSING_MISSING_SPECIAL_TARGET;
		return ;
	}
	parser_special_redirect_out_more(parser, token, fd);
}
