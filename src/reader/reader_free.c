/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:34:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/17 13:39:32 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include <readline/readline.h>

void	reader_free(t_reader *reader)
{
	size_t	i;

	if (reader == NULL)
		return ;
	if (reader->cached)
		free(reader->cached);
	if (reader->cached_input)
		free(reader->cached_input);
	if (reader->lexer)
		free_lexer(reader->lexer);
	if (reader->parser)
		parser_free(reader->parser);
	if (reader->tokens)
		ft_lstclear(&reader->tokens, (void (*)(void *))free_token);
	if (reader->env)
		ft_lstclear(&reader->env, free);
	if (reader->linereader)
	{
		if (reader->linereader->line)
			free(reader->linereader->line);
		free(reader->linereader);
	}
	if (reader->commands)
	{
		i = 0;
		while (reader->commands[i].args)
		{
			free_command_contents(&reader->commands[i]);
			i++;
		}
		free(reader->commands);
	}
	if (reader->varnames)
		free(reader->varnames);
	free(reader);
	rl_clear_history();
	errno = 0;
}
