/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:41:12 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/16 19:34:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "reader.h"
#include "shared.h"
#include "utils.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void	print_tokens(t_list *tokens)
{
	t_list	*current;
	t_token	*token;

	current = tokens;
	while (current)
	{
		token = (t_token *)current->content;
		if (token)
		{
			printf("Token: '%s', Type: %d\n", token->value, token->type);
		}
		current = current->next;
	}
}

void	print_parser(t_parser *parser)
{
	t_list	*current;
	t_cmd	*cmd;

	if (!parser)
	{
		printf("Parser is NULL\n");
		return ;
	}
	// print the tokens
	printf("Parser State: %d\n", parser->state);
	printf("Current Index: %zu\n", parser->current_index);
	printf("Token Count: %zu\n", parser->token_count);
	if (parser->command_list)
	{
		printf("Command List:\n");
		current = parser->command_list;
		while (current)
		{
			cmd = (t_cmd *)current->content;
			if (cmd)
			{
				printf("Command: %s, Arg Count: %d", cmd->args[0], cmd->argc);
				if (cmd->is_pipe)
					printf(" (Pipe)");
				if (cmd->fd_infile != -1)
					printf(", Infile: %d", cmd->fd_infile);
				if (cmd->fd_outfile != -1)
					printf(", Outfile: %d", cmd->fd_outfile);
				if (cmd->redirect_in)
					printf(", Redirect In: %s", cmd->redirect_in);
				if (cmd->redirect_out)
					printf(", Redirect Out: %s", cmd->redirect_out);
				if (cmd->redirect_append)
					printf(", Redirect Append: %s", cmd->redirect_append);
				if (cmd->redirect_heredoc)
					printf(", Redirect Heredoc: %s", cmd->redirect_heredoc);
				printf("\n");
			}
			current = current->next;
		}
	}
	else
	{
		printf("No commands parsed.\n");
	}
}

// New: process here-documents for parsed commands
void	process_heredocs(t_cmd *cmds, t_list *env)
{
	size_t	i;
	char	*line;
	t_file	*f;
	t_list	*delim_node;
	char	*delimiter;
	char	*last_delimiter;

	(void)env;
	for (i = 0; cmds[i].args; ++i)
	{
		if (cmds[i].heredoc_delimiters)
		{
			// Process all heredoc delimiters, but only use the last one
			delim_node = cmds[i].heredoc_delimiters;
			last_delimiter = NULL;
			f = NULL;
			// Find the last delimiter
			while (delim_node)
			{
				last_delimiter = (char *)delim_node->content;
				delim_node = delim_node->next;
			}
			// Process each heredoc delimiter
			delim_node = cmds[i].heredoc_delimiters;
			while (delim_node)
			{
				delimiter = (char *)delim_node->content;
				// Only open the temp file for the last delimiter
				if (delimiter == last_delimiter)
				{
					f = ft_opentmp(ft_openurand(), true);
					if (!f)
					{
						perror("heredoc");
						break ;
					}
				}
				// Always prompt for input for each heredoc
				while (true)
				{
					line = readline("heredoc> ");
					if (!line)
						break ;
					if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
						&& ft_strlen(line) == ft_strlen(delimiter))
					{
						free(line);
						break ;
					}
					// Only write to file if this is the last heredoc
					if (delimiter == last_delimiter && f)
					{
						ft_putstr_fd(line, f->fd);
						ft_putstr_fd("\n", f->fd);
					}
					free(line);
				}
				delim_node = delim_node->next;
			}
			// Set the file descriptor for the last heredoc
			if (f)
			{
				lseek(f->fd, 0, SEEK_SET);
				cmds[i].fd_infile = f->fd;
				free(f);
			}
		}
		else if (cmds[i].redirect_heredoc)
		{
			// Fallback for backward compatibility
			f = ft_opentmp(ft_openurand(), true);
			if (!f)
			{
				perror("heredoc");
				continue ;
			}
			while (true)
			{
				line = readline("heredoc> ");
				if (!line)
					break ;
				if (ft_strncmp(line, cmds[i].redirect_heredoc,
						ft_strlen(cmds[i].redirect_heredoc)) == 0)
				{
					free(line);
					break ;
				}
				ft_putstr_fd(line, f->fd);
				ft_putstr_fd("\n", f->fd);
				free(line);
			}
			lseek(f->fd, 0, SEEK_SET);
			cmds[i].fd_infile = f->fd;
			free(f);
		}
	}
}
