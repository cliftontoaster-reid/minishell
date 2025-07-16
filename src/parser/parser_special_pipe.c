/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 12:00:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/// @brief Handles the pipe token when in the PARSER_SPECIAL state.
/// It checks for syntax errors (e.g., double pipes, pipe at the end of input)
/// and sets the is_pipe flag in the current command structure.
/// @param parser The parser instance.
void	parser_special_pipe(t_parser *parser)
{
	if (parser->command == NULL)
		parser->command = cmd_init();
	parser->command->is_pipe = true;
	end_command(parser);
	parser->state = PARSER_NONE;
}
