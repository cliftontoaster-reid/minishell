/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:49:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:41:12 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "reader.h"
#include "shared.h"
#include "sigint.h"
#include "utils.h"
#include "varextract.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

#define PROMPT "picoshell> "
#define BOLD "\033[1m"
#define RESET "\033[0m"

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
static void	process_heredocs(t_cmd *cmds, t_list *env)
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

t_cmd	*remove_empty_commands(t_cmd *commands)
{
	size_t	count;
	size_t	valid_count;
	size_t	i;
	size_t	j;
	t_cmd	*new_commands;

	if (!commands)
		return (NULL);
	// Count total commands and valid commands
	count = 0;
	valid_count = 0;
	while (commands[count].args)
	{
		if (commands[count].argc > 0)
			valid_count++;
		count++;
	}
	// Allocate new array for valid commands + null terminator
	new_commands = ft_calloc(valid_count + 1, sizeof(t_cmd));
	if (!new_commands)
		return (NULL);
	// Copy valid commands to new array
	j = 0;
	for (i = 0; i < count; i++)
	{
		if (commands[i].argc > 0)
		{
			new_commands[j] = commands[i];
			j++;
		}
		// Note: Don't free empty commands here - they're still referenced
		// in the parser's command list and will be freed by parser_free()
	}
	// Null-terminate the new array
	ft_bzero(&new_commands[valid_count], sizeof(t_cmd));
	new_commands[valid_count].args = NULL;
	new_commands[valid_count].argc = -1;
	// Free the original commands array
	free(commands);
	return (new_commands);
}

int	main(int argc, char **argv, char **envp)
{
	t_reader		*reader_ptr;
	char			*cached_input;
	t_linereader	reader;
	t_cmd			*commands;
	t_list			*varlists;
	t_list			*vl_node;
	size_t			cmd_idx;
	t_list			*vl;
	int				n;
	char			**varnames;
	int				vi;
	t_list			*it;
	t_list			*inner;
	t_list			*next;

	ft_bzero(&reader, sizeof(t_linereader));
	cached_input = NULL;
	reader_ptr = reader_init(envp);
	// Disable readline's default signal handling to use custom handlers
	rl_catch_signals = 0;
	register_reader();
	(void)argc;
	(void)argv;
	while (1)
	{
		print_prompt(reader_ptr->env);
		cached_input = readline(PROMPT);
		add_history(cached_input);
		if (!cached_input)
		{
			if (errno == EINTR)
				continue ; // Handle interrupted read
			// Print exit on EOF (Ctrl+D)
			write(1, "exit\n", 5);
			break ; // Exit on EOF or error
		}
		handle_read(reader_ptr, cached_input);
		free(cached_input);
		cached_input = NULL;
		/// Parser printing
		if (reader_ptr->parser)
		{
			commands = parser_to_list(reader_ptr->parser);
			// Variable expansion for each command argument
			{
				varlists = reader_ptr->vars;
				vl_node = varlists;
				cmd_idx = 0;
				while (vl_node && commands[cmd_idx].args
					&& commands[cmd_idx].argc)
				{
					vl = (t_list *)vl_node->content;
					n = ft_lstsize(vl);
					varnames = malloc(sizeof(char *) * (n + 1));
					if (varnames)
					{
						vi = 0;
						it = vl;
						while (it)
						{
							varnames[vi++] = it->content;
							it = it->next;
						}
						varnames[vi] = NULL;
						for (int ai = 0; commands[cmd_idx].args[ai]; ai++)
							commands[cmd_idx].args[ai] = ft_var(commands[cmd_idx].args[ai],
									varnames, reader_ptr->env);
						free(varnames);
					}
					vl_node = vl_node->next;
					cmd_idx++;
				}
				// Free varlists and inner lists
				vl_node = varlists;
				while (vl_node)
				{
					inner = vl_node->content;
					ft_lstclear(&inner, free);
					next = vl_node->next;
					free(vl_node);
					vl_node = next;
				}
			}
			// read heredoc bodies before execution
			if (commands)
				process_heredocs(commands, reader_ptr->env);
			commands = remove_empty_commands(commands);
			if (cached_input)
			{
				free(cached_input);
				cached_input = NULL;
			}
			ft_pipex(commands, reader_ptr->env, reader_ptr);
			parser_free(reader_ptr->parser);
			reader_ptr->parser = NULL;
		}
		if (reader_ptr->lexer)
		{
			free_lexer(reader_ptr->lexer);
			reader_ptr->lexer = NULL;
		}
		reader_ptr->tokens = NULL;
	}
	// free reader resources
	if (cached_input)
		free(cached_input);
	if (reader_ptr->lexer)
		free_lexer(reader_ptr->lexer);
	if (reader_ptr->parser)
		parser_free(reader_ptr->parser);
	if (reader_ptr->tokens)
		ft_lstclear(&reader_ptr->tokens, (void (*)(void *))free_token);
	if (reader_ptr->env)
		ft_lstclear(&reader_ptr->env, free);
	if (reader_ptr)
		free(reader_ptr);
	if (reader.line)
		free(reader.line);
	clear_history();
	return (g_status_code);
}
