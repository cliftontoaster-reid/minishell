/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_read_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:23:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

bool	handle_read_two(t_reader *reader)
{
	if (!try_lex(reader))
	{
		free(reader->cached);
		reader->cached = NULL;
		errno = EINVAL;
		return (true);
	}
	if (!try_parse(reader))
	{
		free(reader->cached);
		reader->cached = NULL;
		free_lexer(reader->lexer);
		reader->lexer = NULL;
		if (reader->tokens)
			reader->tokens = NULL;
		errno = EINVAL;
		return (true);
	}
	return (false);
}
