/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:38:30 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/23 18:38:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <errno.h>
#include <unistd.h>

static inline size_t	get_command_list_size(t_parser *parser)
{
	size_t	len;

	len = ft_lstsize(parser->command_list);
	if (len == 0)
	{
		errno = EINVAL;
		return (0);
	}
	return (len);
}

static inline t_cmd	*allocate_commands_array(size_t len)
{
	t_cmd	*commands;

	commands = ft_calloc(len + 1, sizeof(t_cmd));
	if (commands == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (commands);
}

static inline void	copy_commands_from_list(t_cmd *commands,
		t_list *command_list, size_t len)
{
	size_t	i;
	t_list	*current;

	i = 0;
	current = command_list;
	while (current && i < len)
	{
		commands[i] = *(t_cmd *)current->content;
		current = current->next;
		i++;
	}
}

static inline void	initialize_sentinel_command(t_cmd *commands, size_t index)
{
	commands[index].args = NULL;
	commands[index].argc = 0;
	commands[index].is_pipe = false;
	commands[index].fd_infile = STDIN_FILENO;
	commands[index].fd_outfile = STDOUT_FILENO;
	commands[index].redirect_in = NULL;
	commands[index].redirect_out = NULL;
	commands[index].redirect_append = NULL;
	commands[index].redirect_heredoc = NULL;
}

t_cmd	*parser_to_list(t_parser *parser)
{
	size_t	len;
	t_cmd	*commands;

	if (parser == NULL || parser->command_list == NULL)
	{
		errno = EINVAL;
		return (NULL);
	}
	len = get_command_list_size(parser);
	if (len == 0)
		return (NULL);
	commands = allocate_commands_array(len);
	if (commands == NULL)
		return (NULL);
	copy_commands_from_list(commands, parser->command_list, len);
	initialize_sentinel_command(commands, len);
	return (commands);
}
