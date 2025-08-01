/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 14:53:23 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "reader.h"

static bool	attach_vars_to_cmds(t_reader *reader)
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
		current = current->next;
		i++;
	}
	return (true);
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
		free_varlists(reader->vars);
		reader->parser = NULL;
		errno = EINVAL;
		g_status_code = 2;
		printf("Parsing error: %s\n", p_strerror(error));
		return (false);
	}
	return (attach_vars_to_cmds(reader));
}
