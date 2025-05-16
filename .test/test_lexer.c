/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:16 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/16 14:49:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "string.h"
#include <criterion/criterion.h>
#include <stdio.h>

void	free_tok(void *token)
{
	free_token((t_token *)token);
}

void	print_tokenlist(t_list *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = token_list->content;
		fprintf(stderr, "Token: %s, Type: %d\n", token->value, token->type);
		token_list = token_list->next;
	}
}

t_token	*get_n_token(t_list *token_list, int n)
{
	t_token	*token;

	token = token_list->content;
	while (n > 0 && token_list->next)
	{
		token_list = token_list->next;
		token = token_list->content;
		n--;
	}
	return (token);
}

const char	*get_token_name(t_token_type type)
{
	const char	*expected_name;

	expected_name = NULL;
	switch (type)
	{
	case TOKEN_NONE:
		expected_name = "TOKEN_NONE";
		break ;
	case TOKEN_WORD:
		expected_name = "TOKEN_WORD";
		break ;
	case TOKEN_PIPE:
		expected_name = "TOKEN_PIPE";
		break ;
	case TOKEN_REDIRECT_IN:
		expected_name = "TOKEN_REDIRECT_IN";
		break ;
	case TOKEN_REDIRECT_OUT:
		expected_name = "TOKEN_REDIRECT_OUT";
		break ;
	case TOKEN_REDIRECT_APPEND:
		expected_name = "TOKEN_REDIRECT_APPEND";
		break ;
	case TOKEN_REDIRECT_HEREDOC:
		expected_name = "TOKEN_REDIRECT_HEREDOC";
		break ;
	default:
		expected_name = "UNKNOWN";
		break ;
	}
	return (expected_name);
}

void	token_test(t_token *token, t_token_type type, char *value, char *name)
{
	const char	*expected_name;
	const char	*actual_name;

	if (!token)
	{
		cr_assert_fail("Expected token to not be NULL for %s", name);
		return ;
	}
	if (!value)
	{
		cr_assert_fail("Expected token value to not be NULL for %s", name);
		return ;
	}
	if (!name)
	{
		cr_assert_fail("Expected token name to not be NULL");
		return ;
	}
	if (!token->value)
	{
		cr_assert_fail("Expected token value to not be NULL for %s", name);
		return ;
	}
	if (token->type != type)
	{
		/* map expected enum to name */
		expected_name = get_token_name(type);
		/* map actual enum to name */
		actual_name = get_token_name(token->type);
		cr_assert_fail("Expected token type to be %s, got %s for %s",
			expected_name, actual_name, name);
		return ;
	}
	if (strcmp(token->value, value) != 0)
	{
		cr_assert_fail("Expected token value to be '%s', got '%s' for %s",
			value, token->value, name);
		return ;
	}
}

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
	cr_assert_not_null(token_list, "Expected token list to be NULL");
	cr_assert(token_list->next == NULL);
	cr_assert_eq(((t_token *)token_list->content)->type, TOKEN_NONE,
		"Expected token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(((t_token *)token_list->content)->value, "   "), 0,
		"Expected token value to be '   '");
	cr_assert_eq(lexer.pos, 3, "Expected lexer position to be 3");
	cr_assert_eq(lexer.state, LEXER_NONE,
		"Expected lexer state to be LEXER_NONE");
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

Test(run_lexer, redirect_in)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "hello < world";
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
	token_test(get_n_token(token_list, 3), TOKEN_REDIRECT_IN, "<",
		"redirect in");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, " ", "whitespace 2");
	token_test(get_n_token(token_list, 5), TOKEN_WORD, "world", "word 2");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, redirect_out)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "hello > world";
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
	token_test(get_n_token(token_list, 3), TOKEN_REDIRECT_OUT, ">",
		"redirect out");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, " ", "whitespace 2");
	token_test(get_n_token(token_list, 5), TOKEN_WORD, "world", "word 2");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, redirect_append)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "hello >> world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be not NULL");
	cr_assert_eq(ft_lstsize(token_list), 6, "Expected token list len 6, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "hello", "word 1");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace 1");
	token_test(get_n_token(token_list, 3), TOKEN_REDIRECT_APPEND, ">>",
		"redirect append");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, " ", "whitespace 2");
	token_test(get_n_token(token_list, 5), TOKEN_WORD, "world", "word 2");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, redirect_heredoc)
{
	t_lexer	lexer;
	t_list	*token_list;

	lexer.text = "hello << world";
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
	token_test(get_n_token(token_list, 3), TOKEN_REDIRECT_HEREDOC, "<<",
		"redirect heredoc");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, " ", "whitespace 2");
	token_test(get_n_token(token_list, 5), TOKEN_WORD, "world", "word 2");
	//
	ft_lstclear(&token_list, free_tok);
}

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
	cr_assert_eq(ft_lstsize(token_list), 5, "Expected token list len 5, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "hello world", "arg");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, "", "end");
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
	cr_assert_eq(ft_lstsize(token_list), 6, "Expected token list len 6, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "hello", "arg");
	token_test(get_n_token(token_list, 4), TOKEN_WORD, " world", "arg 2");
	token_test(get_n_token(token_list, 5), TOKEN_NONE, "", "end");
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
	cr_assert_eq(ft_lstsize(token_list), 5, "Expected token list len 5, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "hello world", "arg");
	token_test(get_n_token(token_list, 4), TOKEN_NONE, "", "end");
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
	cr_assert_eq(ft_lstsize(token_list), 6, "Expected token list len 6, got %d",
		ft_lstsize(token_list));
	//
	token_test(get_n_token(token_list, 0), TOKEN_NONE, "", "start");
	token_test(get_n_token(token_list, 1), TOKEN_WORD, "ls", "command");
	token_test(get_n_token(token_list, 2), TOKEN_NONE, " ", "whitespace");
	token_test(get_n_token(token_list, 3), TOKEN_WORD, "hello", "arg");
	token_test(get_n_token(token_list, 4), TOKEN_WORD, " world", "arg 2");
	token_test(get_n_token(token_list, 5), TOKEN_NONE, "", "end");
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
	cr_assert_eq(ft_lstsize(token_list), 9, "Expected token list len 9, got %d",
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
	token_test(get_n_token(token_list, 8), TOKEN_NONE, "", "end");
	ft_lstclear(&token_list, free_tok);
}

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
	cr_assert_eq(ft_lstsize(token_list), 32, "Expected 32 tokens, got %d",
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
	token_test(get_n_token(token_list, 31), TOKEN_NONE, "", "end");
	//
	ft_lstclear(&token_list, free_tok);
}
