/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_join_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:21:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

Test(join_words, simple)
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
	join_words(&lexer);
	cr_assert_eq(ft_lstsize(token_list), 4, "The token list should not change");
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "hello", "word 1");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "world", "word 2");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(join_words, simple_adjacent)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "hello world'hello'";
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
	join_words(&lexer);
	cr_assert_eq(ft_lstsize(token_list), 4,
		"Expected token list len 4 after join, got %d", ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "hello", "word 1");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "worldhello", "word 2");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(join_words, simple_adjacent_2)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "hello world'hello' world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	cr_assert_eq(ft_lstsize(token_list), 7, "Expected token list len 7, got %d",
		ft_lstsize(token_list));
	join_words(&lexer);
	cr_assert_eq(ft_lstsize(token_list), 6,
		"Expected token list len 6 after join, got %d", ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "hello", "word 1");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "worldhello", "word 2");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 5), TOKEN_WORD, "world", "word 3");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(join_words, simple_adjacent_3)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "Bury t'he' \"light deep\" within";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
	cr_assert_eq(ft_lstsize(token_list), 9, "Expected token list len 8, got %d",
		ft_lstsize(token_list));
	join_words(&lexer);
	cr_assert_eq(ft_lstsize(token_list), 8,
		"Expected token list len 7 after join, got %d", ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "Bury", "word 1");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "the", "word 2");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 5), TOKEN_WORD, "light deep", "word 4");
	token_test(get_n_token(token_list, 6), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 7), TOKEN_WORD, "within", "word 5");
	//
	ft_lstclear(&token_list, free_tok);
}

// Tests based on "Bury the Light" lyrics
Test(join_words, lyric_I_am_the_storm)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "I am the storm that is approaching";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	join_words(&lexer);
	cr_assert_eq(ft_lstsize(token_list), 14, "Expected 14 tokens, got %d",
		ft_lstsize(token_list));
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "I", "lyric1 start");
	token_test(get_n_token(token_list, 13), TOKEN_WORD, "approaching",
		"lyric1 end");
	ft_lstclear(&token_list, free_tok);
}

Test(join_words, lyric_Provoking)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "Provoking";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	join_words(&lexer);
	cr_assert_eq(ft_lstsize(token_list), 2, "Expected 2 tokens, got %d",
		ft_lstsize(token_list));
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "Provoking",
		"lyric2 single");
	ft_lstclear(&token_list, free_tok);
}
