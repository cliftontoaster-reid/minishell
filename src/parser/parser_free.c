/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:35:34 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/06 14:52:53 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_command(void *data)
{
	t_command	*command;

	command = (t_command *)data;
	if (command == NULL)
		return ;
	if (command->name != NULL)
		free(command->name);
	if (command->args != NULL)
	{
		for (size_t i = 0; command->args[i] != NULL; i++)
			free(command->args[i]);
		free(command->args);
	}
	free(command);
}

void	parser_free(t_parser *parser)
{
	if (parser == NULL)
		return ;
	if (parser->command_list != NULL)
		ft_lstclear(&parser->command_list, free_command);
	if (parser->token_list != NULL)
		ft_lstclear(&parser->token_list, (void (*)(void *))free_token);
	if (parser->command != NULL)
		free_command(parser->command);
	free(parser);
	parser = NULL;
}
