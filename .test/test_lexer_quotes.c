/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:21:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

Test(run_lexer, duo_simple)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "ls \"hello world\"";
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
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "hello world", "arg");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, duo_messy)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "ls hello\" world\"";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	cr_assert_eq(ft_lstsize(token_list), 5, "Expected token list len 5, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "hello", "arg");
	token_test(get_n_token(token_list, 4), TOKEN_WORD, " world", "arg 2");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, uni_simple)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "ls 'hello world'";
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
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "hello world", "arg");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, uni_messy)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "ls hello' world'";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	cr_assert_eq(ft_lstsize(token_list), 5, "Expected token list len 5, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "hello", "arg");
	token_test(get_n_token(token_list, 4), TOKEN_WORD, " world", "arg 2");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, uno_dos_holyfuck)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "ls owo\"hello' world\" uwu'hello\" world'";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	cr_assert_eq(ft_lstsize(token_list), 8, "Expected token list len 9, got %d",
		ft_lstsize(token_list));
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace 1");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "owo", "word 1");
	token_test(get_n_token(token_list, 4), TOKEN_WORD, "hello' world",
		"quoted 1");
	token_test(get_n_token(token_list, 5), TOKEN_NONE, " ", "whitespace 2");
	token_test(get_n_token(token_list, 6), TOKEN_WORD, "uwu", "word 2");
	token_test(get_n_token(token_list, 7), TOKEN_WORD, "hello\" world",
		"quoted 2");
	//
	ft_lstclear(&token_list, free_tok);
}
