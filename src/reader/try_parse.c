/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:23:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

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
