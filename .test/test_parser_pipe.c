/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:56:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/14 08:03:27 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "test_utils.h"
#include <criterion/criterion.h>
#include <stdio.h>

Test(parser, pipe_grep)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;
	t_cmd			*command;
	t_cmd			*command2;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "cat file.txt | grep -i pattern";
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
	command2 = (t_cmd *)parser->command_list->next->content;
	cr_assert_not_null(command, "Command should not be NULL");
	cr_assert_not_null(command->args, "Command args should not be NULL");
	cr_assert_eq(command->argc, 2, "Command should have 2 arguments, got %d",
		command->argc);
	cr_assert_str_eq(command->args[0], "cat", "First command should be 'cat'");
	cr_assert_str_eq(command->args[1], "file.txt",
		"Second command should be 'file.txt'");
	cr_assert(command->is_pipe, "First command should be a pipe command");
	cr_assert_not_null(command2, "Second command should not be NULL");
	cr_assert_not_null(command2->args,
		"Second command args should not be NULL");
	cr_assert_eq(command2->argc, 3, "Second command should have 3 args %d",
		command2->argc);
	cr_assert_str_eq(command2->args[0], "grep",
		"First argument of second command should be 'grep'");
	cr_assert_str_eq(command2->args[1], "-i",
		"Second argument of second command should be '-i'");
	cr_assert_str_eq(command2->args[2], "pattern",
		"Third argument of second command should be 'pattern'");
	cr_assert(!command2->is_pipe,
		"Second command should not be a pipe command");
	// Test redirection fields for first command
	cr_assert_null(command->redirect_in,
		"First command should have no input redirection");
	cr_assert_null(command->redirect_out,
		"First command should have no output redirection");
	cr_assert_null(command->redirect_append,
		"First command should have no append redirection");
	cr_assert_null(command->redirect_heredoc,
		"First command should have no heredoc redirection");
	// Test redirection fields for second command
	cr_assert_null(command2->redirect_in,
		"Second command should have no input redirection");
	cr_assert_null(command2->redirect_out,
		"Second command should have no output redirection");
	cr_assert_null(command2->redirect_append,
		"Second command should have no append redirection");
	cr_assert_null(command2->redirect_heredoc,
		"Second command should have no heredoc redirection");
	// Test that args arrays are null-terminated
	cr_assert_null(command->args[command->argc],
		"First command args should be null-terminated");
	cr_assert_null(command2->args[command2->argc],
		"Second command args should be null-terminated");
	// Clean up
	parser_free(parser);
	lexer->token_list = NULL; // Prevent free_lexer from freeing tokens
	lexer->text = NULL;       // Prevent free_lexer from freeing text
	free_lexer(lexer);
}

// Test parsing of a three-command pipeline: echo foo | grep f | wc -l
Test(parser, pipe_double_chain)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;

	t_cmd *c1, *c2, *c3;
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "echo foo | grep f | wc -l";
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
	c1 = parser->command_list->content;
	c2 = parser->command_list->next->content;
	c3 = parser->command_list->next->next->content;
	// First command: echo foo
	cr_assert_eq(c1->argc, 2, "c1 argc should be 2");
	cr_assert_str_eq(c1->args[0], "echo", "c1 args[0] should be 'echo'");
	cr_assert_str_eq(c1->args[1], "foo", "c1 args[1] should be 'foo'");
	cr_assert(c1->is_pipe, "c1 should have is_pipe true");
	cr_assert_null(c1->redirect_in, "c1 redirect_in should be NULL");
	cr_assert_null(c1->redirect_out, "c1 redirect_out should be NULL");
	// Second command: grep f
	cr_assert_eq(c2->argc, 2, "c2 argc should be 2");
	cr_assert_str_eq(c2->args[0], "grep", "c2 args[0] should be 'grep'");
	cr_assert_str_eq(c2->args[1], "f", "c2 args[1] should be 'f'");
	cr_assert(c2->is_pipe, "c2 should have is_pipe true");
	cr_assert_null(c2->redirect_in, "c2 redirect_in should be NULL");
	cr_assert_null(c2->redirect_out, "c2 redirect_out should be NULL");
	// Third command: wc -l
	cr_assert_eq(c3->argc, 2, "c3 argc should be 2");
	cr_assert_str_eq(c3->args[0], "wc", "c3 args[0] should be 'wc'");
	cr_assert_str_eq(c3->args[1], "-l", "c3 args[1] should be '-l'");
	cr_assert(!c3->is_pipe, "c3 should have is_pipe false");
	cr_assert_null(c3->redirect_in, "c3 redirect_in should be NULL");
	cr_assert_null(c3->redirect_out, "c3 redirect_out should be NULL");
	// Clean up
	parser_free(parser);
	lexer->token_list = NULL;
	lexer->text = NULL;
	free_lexer(lexer);
}

// Test parsing of pipeline with redirections: cat < input.txt | sort > output.txt
Test(parser, pipe_with_redirection)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "cat < input.txt | output.txt";
	lexer->pos = 0;
	lexer->state = LEXER_NONE;
	lexer->start = 0;
	lexer->token_list = NULL;
	tokens = run_lexer(lexer);
	parser = parser_init(tokens);
	cr_assert_not_null(parser, "Parser should not be NULL");
	error = parser_parse(parser);
	cr_assert_eq(error, PARSING_ERROR_MALLOC,
		"Parsing should fail with double special directive error");
	// Clean up
	parser_free(parser);
	lexer->token_list = NULL;
	lexer->text = NULL;
	free_lexer(lexer);
}
