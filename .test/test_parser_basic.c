/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_basic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:56:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/13 03:53:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "test_utils.h"
#include <criterion/criterion.h>
#include <stdio.h>

Test(parser, basic_grep)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;
	t_cmd			*command;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "grep -i pattern file.txt";
	lexer->pos = 0;
	lexer->state = LEXER_NONE;
	lexer->start = 0;
	lexer->token_list = NULL;
	tokens = run_lexer(lexer);
	parser = parser_init(tokens);
	cr_assert_not_null(parser, "Parser should not be NULL");
	error = parser_parse(parser);
	// print error if any
	if (error != PARSING_NO_ERROR)
		fprintf(stderr, "Parsing error: %d\n", error);
	cr_assert_eq(error, PARSING_NO_ERROR,
		"Parsing should succeed without errors");
	cr_assert_null(parser->command, "Command should be NULL");
	cr_assert_not_null(parser->command_list, "Command list should not be NULL");
	command = parser->command_list->content;
	cr_assert_not_null(command, "Command should not be NULL");
	cr_assert_not_null(command->args, "Command args should not be NULL");
	cr_assert_eq(command->argc, 4, "Command should have 4 arguments, got %d",
		command->argc);
	cr_assert_str_eq(command->args[0], "grep",
		"First argument should be 'grep'");
	cr_assert_str_eq(command->args[1], "-i", "Second argument should be '-i'");
	cr_assert_str_eq(command->args[2], "pattern",
		"Third argument should be 'pattern'");
	cr_assert_str_eq(command->args[3], "file.txt",
		"Fourth argument should be 'file.txt'");
	// Clean up
	parser_free(parser);
	lexer->token_list = NULL; // Prevent free_lexer from freeing tokens
	lexer->text = NULL;       // Prevent free_lexer from freeing text
	free_lexer(lexer);
}

Test(parser, basic_ls)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;
	t_cmd			*command;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "ls -l /home/user";
	lexer->pos = 0;
	lexer->state = LEXER_NONE;
	lexer->start = 0;
	lexer->token_list = NULL;
	tokens = run_lexer(lexer);
	parser = parser_init(tokens);
	cr_assert_not_null(parser, "Parser should not be NULL");
	error = parser_parse(parser);
	// print error if any
	if (error != PARSING_NO_ERROR)
		fprintf(stderr, "Parsing error: %d\n", error);
	cr_assert_eq(error, PARSING_NO_ERROR,
		"Parsing should succeed without errors");
	cr_assert_null(parser->command, "Command should be NULL");
	cr_assert_not_null(parser->command_list, "Command list should not be NULL");
	command = parser->command_list->content;
	cr_assert_not_null(command, "Command should not be NULL");
	cr_assert_not_null(command->args, "Command args should not be NULL");
	cr_assert_eq(command->argc, 3, "Command should have 3 arguments, got %d",
		command->argc);
	cr_assert_str_eq(command->args[0], "ls", "First argument should be 'ls'");
	cr_assert_str_eq(command->args[1], "-l", "Second argument should be '-l'");
	cr_assert_str_eq(command->args[2], "/home/user",
		"Third argument should be '/home/user'");
	// Clean up
	parser_free(parser);
	lexer->token_list = NULL; // Prevent free_lexer from freeing tokens
	lexer->text = NULL;       // Prevent free_lexer from freeing text
	free_lexer(lexer);
}

Test(parser, basic_echo)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;
	t_cmd			*command;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "echo hello world";
	lexer->pos = 0;
	lexer->state = LEXER_NONE;
	lexer->start = 0;
	lexer->token_list = NULL;
	tokens = run_lexer(lexer);
	parser = parser_init(tokens);
	cr_assert_not_null(parser, "Parser should not be NULL");
	error = parser_parse(parser);
	cr_assert_eq(error, PARSING_NO_ERROR,
		"Parsing should succeed without errors");
	cr_assert_null(parser->command, "Command should be NULL");
	cr_assert_not_null(parser->command_list, "Command list should not be NULL");
	command = parser->command_list->content;
	cr_assert_not_null(command, "Command should not be NULL");
	cr_assert_not_null(command->args, "Command args should not be NULL");
	cr_assert_eq(command->argc, 3, "Command should have 3 arguments, got %d",
		command->argc);
	cr_assert_str_eq(command->args[0], "echo",
		"First argument should be 'echo'");
	cr_assert_str_eq(command->args[1], "hello",
		"Second argument should be 'hello'");
	cr_assert_str_eq(command->args[2], "world",
		"Third argument should be 'world'");
	parser_free(parser);
	lexer->token_list = NULL;
	lexer->text = NULL;
	free_lexer(lexer);
}

Test(parser, single_command)
{
	t_parser *parser;
	t_list *tokens;
	t_lexer *lexer;
	t_parsing_error error;
	t_cmd *command;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "pwd";
	lexer->pos = 0;
	lexer->state = LEXER_NONE;
	lexer->start = 0;
	lexer->token_list = NULL;
	tokens = run_lexer(lexer);

	parser = parser_init(tokens);
	cr_assert_not_null(parser, "Parser should not be NULL");

	error = parser_parse(parser);
	cr_assert_eq(error, PARSING_NO_ERROR,
		"Parsing should succeed without errors");

	cr_assert_null(parser->command, "Command should be NULL");
	cr_assert_not_null(parser->command_list, "Command list should not be NULL");

	command = parser->command_list->content;
	cr_assert_not_null(command, "Command should not be NULL");
	cr_assert_not_null(command->args, "Command args should not be NULL");
	cr_assert_eq(command->argc, 1, "Command should have 1 argument, got %d",
		command->argc);
	cr_assert_str_eq(command->args[0], "pwd", "First argument should be 'pwd'");

	parser_free(parser);
	lexer->token_list = NULL;
	lexer->text = NULL;
	free_lexer(lexer);
}