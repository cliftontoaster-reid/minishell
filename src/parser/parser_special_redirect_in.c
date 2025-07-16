/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_redirect_in.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 12:00:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

/// @brief Handles the input redirection token ('<') when in the PARSER_SPECIAL
/// state. It retrieves the target filename for the redirection and stores it in
/// the command structure. Sets parser error on issues like missing target or
/// memory allocation failure. If there's already an input redirection,
///	it closes the previous file descriptor and replaces it with the new one.
/// @param parser The parser instance.
void	parser_special_redirect_in(t_parser *parser)
{
	t_token	*token;
	int		fd;

	token = get_redirect_token(parser);
	if (!token)
	{
		return ;
	}
	fd = open(token->value, O_RDONLY);
	if (fd < 0)
	{
		errno = EINVAL;
		parser->error = PARSING_MISSING_SPECIAL_TARGET;
		return ;
	}
}
