/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_read_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/24 13:13:05 by jfranc           ###   ########.fr       */
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
