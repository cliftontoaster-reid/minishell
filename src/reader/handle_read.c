/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:53 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/15 16:14:57 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "reader.h"
#include "varextract.h"

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
	reader->vars = b_varextract(reader->lexer->token_list);
	join_words(reader->lexer);
	return (true);
}

static void	attach_vars_to_cmds(t_reader *reader)
{
	t_list	*current;
	int		i;
	int		len;
	t_cmd	*cmd;

	i = 0;
	current = reader->vars;
	len = ft_lstsize(reader->parser->command_list);
	while (current)
	{
		if (current->content == NULL)
		{
			current = current->next;
			continue ;
		}
		cmd = (t_cmd *)ft_lstget(reader->parser->command_list, i, len);
		if (cmd && cmd->args != NULL)
			cmd->var_list = (t_list *)current->content;
		printf("Command %s has %d variables\n", cmd->args[0],
			ft_lstsize(cmd->var_list));
		current = current->next;
		i++;
	}
}

bool	try_parse(t_reader *reader)
{
	t_parsing_error	error;

	if (reader == NULL || reader->tokens == NULL)
	{
		errno = EINVAL;
		return (false);
	}
	reader->parser = parser_init(reader->tokens);
	if (reader->parser == NULL)
	{
		errno = ENOMEM;
		return (false);
	}
	error = parser_parse(reader->parser);
	if (error != PARSING_NO_ERROR)
	{
		parser_free(reader->parser);
		reader->parser = NULL;
		errno = EINVAL;
		printf("Parsing error: %s\n", p_strerror(error));
		return (false);
	}
	attach_vars_to_cmds(reader);
	return (true);
}

bool	str_is_whitespace(const char *str)
{
	if (str == NULL)
		return (false);
	while (*str)
	{
		if (!ft_ciswhite(*str))
			return (false);
		str++;
	}
	return (true);
}

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
	if (str_is_whitespace(reader->cached))
	{
		free(reader->cached);
		reader->cached = NULL;
		return ;
	}
	if (handle_read_two(reader))
		return ;
	free(reader->cached);
	reader->cached = NULL;
}
