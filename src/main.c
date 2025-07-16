/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:49:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 19:37:32 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main_extra.h"
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

int	main(int argc, char **argv, char **envp)
{
	t_reader		*reader_ptr;
	t_list			*varlists;
	t_list			*vl_node;
	size_t			cmd_idx;
	t_list			*vl;
	int				n;
	int				vi;
	t_list			*it;
	t_list			*inner;
	t_list			*next;

	reader_ptr = reader_init(envp);
	// Disable readline's default signal handling to use custom handlers
	rl_catch_signals = 0;
	register_reader();
	(void)argc;
	(void)argv;
	while (1)
	{
		print_prompt(reader_ptr->env);
		reader_ptr->cached_input = readline(PROMPT);
		add_history(reader_ptr->cached_input);
		if (!reader_ptr->cached_input)
		{
			if (errno == EINTR)
				continue ; // Handle interrupted read
			// Print exit on EOF (Ctrl+D)
			write(1, "exit\n", 5);
			break ; // Exit on EOF or error
		}
		handle_read(reader_ptr, reader_ptr->cached_input);
		free(reader_ptr->cached_input);
		reader_ptr->cached_input = NULL;
		/// Parser printing
		if (reader_ptr->parser)
		{
			reader_ptr->commands = parser_to_list(reader_ptr->parser);
			// Variable expansion for each command argument
			{
				varlists = reader_ptr->vars;
				vl_node = varlists;
				cmd_idx = 0;
				while (vl_node && reader_ptr->commands[cmd_idx].args
					&& reader_ptr->commands[cmd_idx].argc)
				{
					vl = (t_list *)vl_node->content;
					n = ft_lstsize(vl);
					reader_ptr->varnames = malloc(sizeof(char *) * (n + 1));
					if (reader_ptr->varnames)
					{
						vi = 0;
						it = vl;
						while (it)
						{
							reader_ptr->varnames[vi++] = it->content;
							it = it->next;
						}
						reader_ptr->varnames[vi] = NULL;
						for (int ai = 0; reader_ptr->commands[cmd_idx].args[ai]; ai++)
							reader_ptr->commands[cmd_idx].args[ai] = ft_var(reader_ptr->commands[cmd_idx].args[ai],
									reader_ptr->varnames, reader_ptr->env);
						free(reader_ptr->varnames);
						reader_ptr->varnames = NULL;
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
			if (reader_ptr->commands)
				process_heredocs(reader_ptr->commands, reader_ptr->env);
			reader_ptr->commands = remove_empty_commands(reader_ptr->commands);
			ft_pipex(reader_ptr->commands, reader_ptr->env, reader_ptr);
			// Free only the commands array itself, not the contents
			// (ft_var already freed and replaced the original argument strings)
			if (reader_ptr->commands)
			{
				free(reader_ptr->commands);
				reader_ptr->commands = NULL;
			}
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
	if (reader_ptr)
		reader_free(reader_ptr);
	clear_history();
	return (g_status_code);
}
