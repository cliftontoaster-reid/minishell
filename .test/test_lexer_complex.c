/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_complex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:21:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

Test(run_lexer, complex)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "ls | grep \"o e\" > result.txt";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	cr_assert_eq(ft_lstsize(token_list), 12,
		"Expected token list size to be 12");
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command 1");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace 1");
	token_test(get_n_token(token_list, 3), TOKEN_PIPE, "|", "pipe");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, " ", "whitespace 2");
	token_test(get_n_token(token_list, 5), TOKEN_WORD, "grep", "command 2");
	token_test(get_n_token(token_list, 6), TOKEN_NONE, " ", "whitespace 3");
	token_test(get_n_token(token_list, 7), TOKEN_WORD, "o e", "arg 1");
	token_test(get_n_token(token_list, 8), TOKEN_NONE, " ", "whitespace 4");
	token_test(get_n_token(token_list, 9), TOKEN_REDIRECT_OUT, ">",
		"redirect out");
	token_test(get_n_token(token_list, 10), TOKEN_NONE, " ", "whitespace 5");
	token_test(get_n_token(token_list, 11), TOKEN_WORD, "result.txt",
		"file name");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, ultimate_messy)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "cmdA 'one two' cmdB\"three four\" | cmdC >out.txt >>append.log <input.dat <<DELIM \"mix'ed\" 'mix\"ed'";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	cr_assert_eq(ft_lstsize(token_list), 31, "Expected 31 tokens, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "cmdA", "word 1");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "ws1");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "one two",
		"single-quoted");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, " ", "ws2");
	token_test(get_n_token(token_list, 5), TOKEN_WORD, "cmdB", "mixed-duo 1");
	token_test(get_n_token(token_list, 6), TOKEN_WORD, "three four",
		"mixed-duo 2");
	token_test(get_n_token(token_list, 7), TOKEN_NONE, " ", "ws3");
	token_test(get_n_token(token_list, 8), TOKEN_PIPE, "|", "pipe");
	token_test(get_n_token(token_list, 9), TOKEN_NONE, " ", "ws4");
	token_test(get_n_token(token_list, 10), TOKEN_WORD, "cmdC", "word 2");
	token_test(get_n_token(token_list, 11), TOKEN_NONE, " ", "ws5");
	token_test(get_n_token(token_list, 12), TOKEN_REDIRECT_OUT, ">",
		"redir out");
	token_test(get_n_token(token_list, 13), TOKEN_NONE, "", "delim 1");
	token_test(get_n_token(token_list, 14), TOKEN_WORD, "out.txt", "out file");
	token_test(get_n_token(token_list, 15), TOKEN_NONE, " ", "ws6");
	token_test(get_n_token(token_list, 16), TOKEN_REDIRECT_APPEND, ">>",
		"redir append");
	token_test(get_n_token(token_list, 17), TOKEN_NONE, "", "delim 2");
	token_test(get_n_token(token_list, 18), TOKEN_WORD, "append.log",
		"append file");
	token_test(get_n_token(token_list, 19), TOKEN_NONE, " ", "ws7");
	token_test(get_n_token(token_list, 20), TOKEN_REDIRECT_IN, "<", "redir in");
	token_test(get_n_token(token_list, 21), TOKEN_NONE, "", "delim 3");
	token_test(get_n_token(token_list, 22), TOKEN_WORD, "input.dat", "in file");
	token_test(get_n_token(token_list, 23), TOKEN_NONE, " ", "ws8");
	token_test(get_n_token(token_list, 24), TOKEN_REDIRECT_HEREDOC, "<<",
		"heredoc");
	token_test(get_n_token(token_list, 25), TOKEN_NONE, "", "delim 4");
	token_test(get_n_token(token_list, 26), TOKEN_WORD, "DELIM",
		"heredoc word");
	token_test(get_n_token(token_list, 27), TOKEN_NONE, " ", "ws9");
	token_test(get_n_token(token_list, 28), TOKEN_WORD, "mix'ed",
		"double-quoted mix");
	token_test(get_n_token(token_list, 29), TOKEN_NONE, " ", "ws10");
	token_test(get_n_token(token_list, 30), TOKEN_WORD, "mix\"ed",
		"single-quoted mix");
	//
	ft_lstclear(&token_list, free_tok);
}
