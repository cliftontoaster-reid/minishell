/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:34:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/16 19:35:15 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

void	reader_free(t_reader *reader)
{
	if (reader == NULL)
		return ;
	if (reader->cached)
		free(reader->cached);
	if (reader->lexer)
		free_lexer(reader->lexer);
	if (reader->parser)
		parser_free(reader->parser);
	free(reader);
	errno = 0;
}
