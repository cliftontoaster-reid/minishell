/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:49:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/04 13:49:50 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "reader.h"
#include "shared.h"
#include "utils.h"
#include <errno.h>
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

int	main(int argc, char **argv, char **envp)
{
	t_list			*env_list;
	t_reader		*reader_ptr;
	char			*cached_input;
	t_linereader	reader;
	t_cmd			*commands;

	ft_bzero(&reader, sizeof(t_linereader));
	env_list = b_fromenvp(envp);
	cached_input = NULL;
	reader_ptr = reader_init(envp);
	(void)argc;
	(void)argv;
	(void)env_list;
	(void)reader_ptr;
	while (1)
	{
		print_prompt(reader_ptr->env);
		if (cached_input)
			free(cached_input);
		cached_input = ft_readline(&reader);
		if (!cached_input)
		{
			if (errno == EINTR)
				continue ; // Handle interrupted read
			break ;        // Exit on EOF or error
		}
		handle_read(reader_ptr, cached_input);
		/// Lexer printing
		if (reader_ptr->lexer && reader_ptr->tokens)
		{
			// printf("%sLexer Tokens:%s\n", BOLD, RESET);
			// print_tokens(reader_ptr->tokens);
		}
		/// Parser printing
		if (reader_ptr->parser)
		{
			// printf("%sParser State:%s\n", BOLD, RESET);
			// print_parser(reader_ptr->parser);
			commands = parser_to_list(reader_ptr->parser);
			ft_pipex(commands, reader_ptr->env);
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
	return (g_status_code);
}
