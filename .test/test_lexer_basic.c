/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_basic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:21:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

Test(run_lexer, empty)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_null(token_list, "Expected token list to be NULL");
	cr_assert_eq(lexer.pos, 0, "Expected lexer position to be 0");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, whitespace)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "   ";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_null(token_list, "Expected token list to be NULL");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, word)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "hello world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	cr_assert_eq(ft_lstsize(token_list), 4, "Expected token list len 4, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "hello", "word 1");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "world", "word 2");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, pipe)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "hello | world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	cr_assert_eq(ft_lstsize(token_list), 6, "Expected token list len 6, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "hello", "word 1");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace 1");
	token_test(get_n_token(token_list, 3), TOKEN_PIPE, "|", "pipe");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, " ", "whitespace 2");
	token_test(get_n_token(token_list, 5), TOKEN_WORD, "world", "word 2");
	//
	ft_lstclear(&token_list, free_tok);
}
