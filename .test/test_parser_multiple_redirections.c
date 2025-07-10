/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_multiple_redirections.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/10 14:19:23 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "test_utils.h"
#include <criterion/criterion.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

Test(parser, multiple_input_redirections)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;
	t_cmd			*command;
	char			content1[] = "content of file1\n";
	char			content2[] = "content of file2\n";

	int fd1, fd2;
	// Create test files
	fd1 = open("/tmp/test_file1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd1, content1, sizeof(content1) - 1);
	close(fd1);
	fd2 = open("/tmp/test_file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd2, content2, sizeof(content2) - 1);
	close(fd2);
	// Test: cat < /tmp/test_file1 < /tmp/test_file2
	// Should use /tmp/test_file2 as input (last redirection wins)
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "cat < /tmp/test_file1 < /tmp/test_file2";
	lexer->pos = 0;
	lexer->state = LEXER_NONE;
	lexer->start = 0;
	lexer->token_list = NULL;
	tokens = run_lexer(lexer);
	parser = parser_init(tokens);
	cr_assert_not_null(parser, "Parser should not be NULL");
	error = parser_parse(parser);
	if (error != PARSING_NO_ERROR)
		fprintf(stderr, "Parsing error: %d\n", error);
	cr_assert_eq(error, PARSING_NO_ERROR,
		"Parsing should succeed without errors");
	cr_assert_null(parser->command, "Command should be NULL");
	cr_assert_not_null(parser->command_list, "Command list should not be NULL");
	command = parser->command_list->content;
	cr_assert_not_null(command, "Command should not be NULL");
	cr_assert_not_null(command->args, "Command args should not be NULL");
	cr_assert_eq(command->argc, 1, "Command should have 1 argument, got %d",
		command->argc);
	cr_assert_str_eq(command->args[0], "cat", "First argument should be 'cat'");
	// Check that redirect_in points to the last file
	cr_assert_not_null(command->redirect_in, "redirect_in should not be NULL");
	cr_assert_str_eq(command->redirect_in, "/tmp/test_file2",
		"redirect_in should be '/tmp/test_file2'");
	// Check that the file descriptor is valid and points to the right file
	cr_assert_neq(command->fd_infile, STDIN_FILENO,
		"fd_infile should not be stdin");
	// Clean up
	parser_free(parser);
	lexer->token_list = NULL;
	lexer->text = NULL;
	free_lexer(lexer);
	unlink("/tmp/test_file1");
	unlink("/tmp/test_file2");
}

Test(parser, multiple_output_redirections)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;
	t_cmd			*command;

	// Test: echo hello > /tmp/test_out1 > /tmp/test_out2
	// Should write to /tmp/test_out2 (last redirection wins)
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "echo hello > /tmp/test_out1 > /tmp/test_out2";
	lexer->pos = 0;
	lexer->state = LEXER_NONE;
	lexer->start = 0;
	lexer->token_list = NULL;
	tokens = run_lexer(lexer);
	parser = parser_init(tokens);
	cr_assert_not_null(parser, "Parser should not be NULL");
	error = parser_parse(parser);
	if (error != PARSING_NO_ERROR)
		fprintf(stderr, "Parsing error: %d\n", error);
	cr_assert_eq(error, PARSING_NO_ERROR,
		"Parsing should succeed without errors");
	cr_assert_null(parser->command, "Command should be NULL");
	cr_assert_not_null(parser->command_list, "Command list should not be NULL");
	command = parser->command_list->content;
	cr_assert_not_null(command, "Command should not be NULL");
	cr_assert_not_null(command->args, "Command args should not be NULL");
	cr_assert_eq(command->argc, 2, "Command should have 2 arguments, got %d",
		command->argc);
	cr_assert_str_eq(command->args[0], "echo",
		"First argument should be 'echo'");
	cr_assert_str_eq(command->args[1], "hello",
		"Second argument should be 'hello'");
	// Check that redirect_out points to the last file
	cr_assert_not_null(command->redirect_out,
		"redirect_out should not be NULL");
	cr_assert_str_eq(command->redirect_out, "/tmp/test_out2",
		"redirect_out should be '/tmp/test_out2'");
	// Check that the file descriptor is valid and points to the right file
	cr_assert_neq(command->fd_outfile, STDOUT_FILENO,
		"fd_outfile should not be stdout");
	// Clean up
	parser_free(parser);
	lexer->token_list = NULL;
	lexer->text = NULL;
	free_lexer(lexer);
	unlink("/tmp/test_out1");
	unlink("/tmp/test_out2");
}

Test(parser, multiple_append_redirections)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;
	t_cmd			*command;

	// Test: echo hello >> /tmp/test_append1 >> /tmp/test_append2
	// Should append to /tmp/test_append2 (last redirection wins)
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "echo hello >> /tmp/test_append1 >> /tmp/test_append2";
	lexer->pos = 0;
	lexer->state = LEXER_NONE;
	lexer->start = 0;
	lexer->token_list = NULL;
	tokens = run_lexer(lexer);
	parser = parser_init(tokens);
	cr_assert_not_null(parser, "Parser should not be NULL");
	error = parser_parse(parser);
	if (error != PARSING_NO_ERROR)
		fprintf(stderr, "Parsing error: %d\n", error);
	cr_assert_eq(error, PARSING_NO_ERROR,
		"Parsing should succeed without errors");
	cr_assert_null(parser->command, "Command should be NULL");
	cr_assert_not_null(parser->command_list, "Command list should not be NULL");
	command = parser->command_list->content;
	cr_assert_not_null(command, "Command should not be NULL");
	cr_assert_not_null(command->args, "Command args should not be NULL");
	cr_assert_eq(command->argc, 2, "Command should have 2 arguments, got %d",
		command->argc);
	cr_assert_str_eq(command->args[0], "echo",
		"First argument should be 'echo'");
	cr_assert_str_eq(command->args[1], "hello",
		"Second argument should be 'hello'");
	// Check that redirect_append points to the last file
	cr_assert_not_null(command->redirect_append,
		"redirect_append should not be NULL");
	cr_assert_str_eq(command->redirect_append, "/tmp/test_append2",
		"redirect_append should be '/tmp/test_append2'");
	// Check that the file descriptor is valid and points to the right file
	cr_assert_neq(command->fd_outfile, STDOUT_FILENO,
		"fd_outfile should not be stdout");
	// Clean up
	parser_free(parser);
	lexer->token_list = NULL;
	lexer->text = NULL;
	free_lexer(lexer);
	unlink("/tmp/test_append1");
	unlink("/tmp/test_append2");
}

Test(parser, multiple_heredoc_redirections)
{
	t_parser		*parser;
	t_list			*tokens;
	t_lexer			*lexer;
	t_parsing_error	error;
	t_cmd			*command;

	// Test: cat << EOF1 << EOF2
	// Should use EOF2 as delimiter (last redirection wins)
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->text = "cat << EOF1 << EOF2";
	lexer->pos = 0;
	lexer->state = LEXER_NONE;
	lexer->start = 0;
	lexer->token_list = NULL;
	tokens = run_lexer(lexer);
	parser = parser_init(tokens);
	cr_assert_not_null(parser, "Parser should not be NULL");
	error = parser_parse(parser);
	if (error != PARSING_NO_ERROR)
		fprintf(stderr, "Parsing error: %d\n", error);
	cr_assert_eq(error, PARSING_NO_ERROR,
		"Parsing should succeed without errors");
	cr_assert_null(parser->command, "Command should be NULL");
	cr_assert_not_null(parser->command_list, "Command list should not be NULL");
	command = parser->command_list->content;
	cr_assert_not_null(command, "Command should not be NULL");
	cr_assert_not_null(command->args, "Command args should not be NULL");
	cr_assert_eq(command->argc, 1, "Command should have 1 argument, got %d",
		command->argc);
	cr_assert_str_eq(command->args[0], "cat", "First argument should be 'cat'");
	// Check that redirect_heredoc points to the last delimiter
	cr_assert_not_null(command->redirect_heredoc,
		"redirect_heredoc should not be NULL");
	cr_assert_str_eq(command->redirect_heredoc, "EOF2",
		"redirect_heredoc should be 'EOF2'");
	// Clean up
	parser_free(parser);
	lexer->token_list = NULL;
	lexer->text = NULL;
	free_lexer(lexer);
}
