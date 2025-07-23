/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:34:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 19:48:04 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "shared.h"
#include <readline/readline.h>
#include <unistd.h>

void	free_env(void *env)
{
	free(((t_env *)env)->key);
	free(((t_env *)env)->value);
	free(env);
}

void	gaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaay(t_reader *reader)
{
	if (reader->cached)
		free(reader->cached);
	if (reader->cached_input)
		free(reader->cached_input);
	if (reader->lexer)
		free_lexer(reader->lexer);
	if (reader->parser)
		parser_free(reader->parser);
	if (reader->history_file > STDERR_FILENO)
	{
		close(reader->history_file);
		reader->history_file = -1;
	}
	if (reader->history_last)
	{
		free(reader->history_last);
		reader->history_last = NULL;
	}
}

void	reader_free(t_reader *reader)
{
	if (reader == NULL)
		return ;
	gaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaay(reader);
	if (reader->env)
		ft_lstclear(&reader->env, free_env);
	if (reader->linereader)
	{
		if (reader->linereader->line)
			free(reader->linereader->line);
		free(reader->linereader);
	}
	if (reader->commands)
	{
		ft_cleanup_cmd(reader->commands);
		free(reader->commands);
		reader->commands = NULL;
	}
	if (reader->varnames)
		free(reader->varnames);
	free(reader);
	rl_clear_history();
}
