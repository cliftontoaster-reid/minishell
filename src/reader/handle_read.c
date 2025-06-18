/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:53 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/18 12:14:44 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "reader.h"

bool	try_read(t_reader *reader, const char *input)
{
	char	*new_cached;

	if (reader->cached != NULL)
	{
		new_cached = ft_strjoin(reader->cached, input);
		if (new_cached == NULL)
		{
			errno = ENOMEM;
			return (false);
		}
		free(reader->cached);
		reader->cached = new_cached;
	}
	else
	{
		reader->cached = ft_strdup(input);
		if (reader->cached == NULL)
		{
			errno = ENOMEM;
			return (false);
		}
	}
	return (true);
}

bool	try_lex(t_reader *reader)
{
	reader->lexer = create_lexer(reader->cached);
	if (reader->lexer == NULL)
	{
		errno = ENOMEM;
		return (false);
	}
	reader->tokens = run_lexer(reader->lexer);
	if (reader->tokens == NULL)
	{
		free_lexer(reader->lexer);
		reader->lexer = NULL;
		errno = EINVAL;
		return (false);
	}
	return (true);
}

void	handle_read(t_reader *reader, const char *input)
{
	if (reader == NULL || input == NULL)
	{
		errno = EINVAL;
		return ;
	}
	if (!try_read(reader, input))
	{
		errno = ENOMEM;
		return ;
	}
}

void	try_read(t_reader *reader)
{
}
