/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_iteration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:08:13 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

void	cleanup_iteration(t_reader *reader_ptr)
{
	if (reader_ptr->commands)
	{
		free(reader_ptr->commands);
		reader_ptr->commands = NULL;
	}
	if (reader_ptr->parser)
	{
		parser_free(reader_ptr->parser);
		reader_ptr->parser = NULL;
	}
	if (reader_ptr->lexer)
	{
		free_lexer(reader_ptr->lexer);
		reader_ptr->lexer = NULL;
	}
	reader_ptr->tokens = NULL;
}
