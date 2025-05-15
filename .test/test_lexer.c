/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:16 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/15 18:25:14 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "string.h"
#include <criterion/criterion.h>

void	free_tok(void *token)
{
	free_token((t_token *)token);
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
	t_token	*start;
	t_token	*hello;
	t_token	*white;
	t_token	*world;

	lexer.text = "hello world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be NULL");
	start = token_list->content;
	cr_assert_not_null(start, "Expected 1st token to not be NULL");
	hello = token_list->next->content;
	cr_assert_not_null(hello, "Expected 2nd token to not be NULL");
	white = token_list->next->next->content;
	cr_assert_not_null(white, "Expected 3rd token to not be NULL");
	world = token_list->next->next->next->content;
	cr_assert_not_null(world, "Expected 4th token to not be NULL");
	cr_assert_null(token_list->next->next->next->next,
		"Expected 5th token to be NULL");
	cr_assert_eq(hello->type, TOKEN_WORD,
		"Expected token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(hello->value, "hello"), 0,
		"Expected token value to be 'hello'");
	cr_assert_eq(white->type, TOKEN_NONE,
		"Expected token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(white->value, " "), 0,
		"Expected token value to be ' '");
	cr_assert_eq(world->type, TOKEN_WORD,
		"Expected token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(world->value, "world"), 0,
		"Expected token value to be 'world'");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, pipe)
{
	t_lexer	lexer;
	t_list	*token_list;
	t_token	*start;
	t_token	*hello;
	t_token	*white_1;
	t_token	*pipe;
	t_token	*white_2;
	t_token	*world;

	lexer.text = "hello | world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be NULL");
	start = token_list->content;
	cr_assert_not_null(start, "Expected 1st token to not be NULL");
	hello = token_list->next->content;
	cr_assert_not_null(hello, "Expected 2nd token to not be NULL");
	white_1 = token_list->next->next->content;
	cr_assert_not_null(white_1, "Expected 3rd token to not be NULL");
	pipe = token_list->next->next->next->content;
	cr_assert_not_null(pipe, "Expected 4th token to not be NULL");
	white_2 = token_list->next->next->next->next->content;
	cr_assert_not_null(white_2, "Expected 5th token to not be NULL");
	world = token_list->next->next->next->next->next->content;
	cr_assert_not_null(world, "Expected 6th token to not be NULL");
	cr_assert_null(token_list->next->next->next->next->next->next,
		"Expected 7th token to be NULL");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, redirect_in)
{
	t_lexer	lexer;
	t_list	*token_list;
	t_token	*start;
	t_token	*hello;
	t_token	*white_1;
	t_token	*redirect_in;
	t_token	*white_2;
	t_token	*world;

	lexer.text = "hello < world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be NULL");
	start = token_list->content;
	cr_assert_not_null(start, "Expected 1st token to not be NULL");
	hello = token_list->next->content;
	cr_assert_not_null(hello, "Expected 2nd token to not be NULL");
	white_1 = token_list->next->next->content;
	cr_assert_not_null(white_1, "Expected 3rd token to not be NULL");
	redirect_in = token_list->next->next->next->content;
	cr_assert_not_null(redirect_in, "Expected 4th token to not be NULL");
	white_2 = token_list->next->next->next->next->content;
	cr_assert_not_null(white_2, "Expected 5th token to not be NULL");
	world = token_list->next->next->next->next->next->content;
	cr_assert_not_null(world, "Expected 6th token to not be NULL");
	cr_assert_null(token_list->next->next->next->next->next->next,
		"Expected 7th token to be NULL");
	//
	cr_assert_eq(start->type, TOKEN_NONE,
		"Expected 1st token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(start->value, ""), 0,
		"Expected 1st token value to be ''");
	cr_assert_eq(hello->type, TOKEN_WORD,
		"Expected 2nd token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(hello->value, "hello"), 0,
		"Expected 2nd token value to be 'hello'");
	cr_assert_eq(white_1->type, TOKEN_NONE,
		"Expected 3rd token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(white_1->value, " "), 0,
		"Expected 3rd token value to be ' '");
	cr_assert_eq(redirect_in->type, TOKEN_REDIRECT_IN,
		"Expected 4th token type to be TOKEN_REDIRECT_IN");
	cr_assert_eq(strcmp(redirect_in->value, "<"), 0,
		"Expected 4th token value to be '<'");
	cr_assert_eq(white_2->type, TOKEN_NONE,
		"Expected 5th token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(white_2->value, " "), 0,
		"Expected 5th token value to be ' '");
	cr_assert_eq(world->type, TOKEN_WORD,
		"Expected 6th token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(world->value, "world"), 0,
		"Expected 6th token value to be 'world'");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, redirect_out)
{
	t_lexer	lexer;
	t_list	*token_list;
	t_token	*start;
	t_token	*hello;
	t_token	*white_1;
	t_token	*redirect_out;
	t_token	*white_2;
	t_token	*world;

	lexer.text = "hello > world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be NULL");
	start = token_list->content;
	cr_assert_not_null(start, "Expected 1st token to not be NULL");
	hello = token_list->next->content;
	cr_assert_not_null(hello, "Expected 2nd token to not be NULL");
	white_1 = token_list->next->next->content;
	cr_assert_not_null(white_1, "Expected 3rd token to not be NULL");
	redirect_out = token_list->next->next->next->content;
	cr_assert_not_null(redirect_out, "Expected 4th token to not be NULL");
	white_2 = token_list->next->next->next->next->content;
	cr_assert_not_null(white_2, "Expected 5th token to not be NULL");
	world = token_list->next->next->next->next->next->content;
	cr_assert_not_null(world, "Expected 6th token to not be NULL");
	cr_assert_null(token_list->next->next->next->next->next->next,
		"Expected 7th token to be NULL");
	//
	cr_assert_eq(start->type, TOKEN_NONE,
		"Expected 1st token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(start->value, ""), 0,
		"Expected 1st token value to be ''");
	cr_assert_eq(hello->type, TOKEN_WORD,
		"Expected 2nd token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(hello->value, "hello"), 0,
		"Expected 2nd token value to be 'hello'");
	cr_assert_eq(white_1->type, TOKEN_NONE,
		"Expected 3rd token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(white_1->value, " "), 0,
		"Expected 3rd token value to be ' '");
	cr_assert_eq(redirect_out->type, TOKEN_REDIRECT_OUT,
		"Expected 4th token type to be TOKEN_REDIRECT_OUT");
	cr_assert_eq(strcmp(redirect_out->value, ">"), 0,
		"Expected 4th token value to be '>'");
	cr_assert_eq(white_2->type, TOKEN_NONE,
		"Expected 5th token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(white_2->value, " "), 0,
		"Expected 5th token value to be ' '");
	cr_assert_eq(world->type, TOKEN_WORD,
		"Expected 6th token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(world->value, "world"), 0,
		"Expected 6th token value to be 'world'");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, redirect_append)
{
	t_lexer	lexer;
	t_list	*token_list;
	t_token	*start;
	t_token	*hello;
	t_token	*white_1;
	t_token	*redirect_append;
	t_token	*white_2;
	t_token	*world;

	lexer.text = "hello >> world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be NULL");
	start = token_list->content;
	cr_assert_not_null(start, "Expected 1st token to not be NULL");
	hello = token_list->next->content;
	cr_assert_not_null(hello, "Expected 2nd token to not be NULL");
	white_1 = token_list->next->next->content;
	cr_assert_not_null(white_1, "Expected 3rd token to not be NULL");
	redirect_append = token_list->next->next->next->content;
	cr_assert_not_null(redirect_append, "Expected 4th token to not be NULL");
	white_2 = token_list->next->next->next->next->content;
	cr_assert_not_null(white_2, "Expected 5th token to not be NULL");
	world = token_list->next->next->next->next->next->content;
	cr_assert_not_null(world, "Expected 6th token to not be NULL");
	cr_assert_null(token_list->next->next->next->next->next->next,
		"Expected 7th token to be NULL");
	//
	cr_assert_eq(start->type, TOKEN_NONE,
		"Expected 1st token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(start->value, ""), 0,
		"Expected 1st token value to be ''");
	cr_assert_eq(hello->type, TOKEN_WORD,
		"Expected 2nd token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(hello->value, "hello"), 0,
		"Expected 2nd token value to be 'hello'");
	cr_assert_eq(white_1->type, TOKEN_NONE,
		"Expected 3rd token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(white_1->value, " "), 0,
		"Expected 3rd token value to be ' '");
	cr_assert_eq(redirect_append->type, TOKEN_REDIRECT_APPEND,
		"Expected 4th token type to be TOKEN_REDIRECT_APPEND");
	cr_assert_eq(strcmp(redirect_append->value, ">>"), 0,
		"Expected 4th token value to be '>>'");
	cr_assert_eq(white_2->type, TOKEN_NONE,
		"Expected 5th token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(white_2->value, " "), 0,
		"Expected 5th token value to be ' '");
	cr_assert_eq(world->type, TOKEN_WORD,
		"Expected 6th token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(world->value, "world"), 0,
		"Expected 6th token value to be 'world'");
	//
	ft_lstclear(&token_list, free_tok);
}

Test(run_lexer, redirect_heredoc)
{
	t_lexer	lexer;
	t_list	*token_list;
	t_token	*start;
	t_token	*hello;
	t_token	*white_1;
	t_token	*redirect_heredoc;
	t_token	*white_2;
	t_token	*world;

	lexer.text = "hello << world";
	lexer.pos = 0;
	lexer.state = LEXER_NONE;
	lexer.start = 0;
	lexer.token_list = NULL;
	token_list = run_lexer(&lexer);
	cr_assert_not_null(token_list, "Expected token list to be NULL");
	start = token_list->content;
	cr_assert_not_null(start, "Expected 1st token to not be NULL");
	hello = token_list->next->content;
	cr_assert_not_null(hello, "Expected 2nd token to not be NULL");
	white_1 = token_list->next->next->content;
	cr_assert_not_null(white_1, "Expected 3rd token to not be NULL");
	redirect_heredoc = token_list->next->next->next->content;
	cr_assert_not_null(redirect_heredoc, "Expected 4th token to not be NULL");
	white_2 = token_list->next->next->next->next->content;
	cr_assert_not_null(white_2, "Expected 5th token to not be NULL");
	world = token_list->next->next->next->next->next->content;
	cr_assert_not_null(world, "Expected 6th token to not be NULL");
	cr_assert_null(token_list->next->next->next->next->next->next,
		"Expected 7th token to be NULL");
	//
	cr_assert_eq(start->type, TOKEN_NONE,
		"Expected 1st token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(start->value, ""), 0,
		"Expected 1st token value to be ''");
	cr_assert_eq(hello->type, TOKEN_WORD,
		"Expected 2nd token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(hello->value, "hello"), 0,
		"Expected 2nd token value to be 'hello'");
	cr_assert_eq(white_1->type, TOKEN_NONE,
		"Expected 3rd token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(white_1->value, " "), 0,
		"Expected 3rd token value to be ' '");
	cr_assert_eq(redirect_heredoc->type, TOKEN_REDIRECT_HEREDOC,
		"Expected 4th token type to be TOKEN_REDIRECT_HEREDOC");
	cr_assert_eq(strcmp(redirect_heredoc->value, "<<"), 0,
		"Expected 4th token value to be '<<'");
	cr_assert_eq(white_2->type, TOKEN_NONE,
		"Expected 5th token type to be TOKEN_NONE");
	cr_assert_eq(strcmp(white_2->value, " "), 0,
		"Expected 5th token value to be ' '");
	cr_assert_eq(world->type, TOKEN_WORD,
		"Expected 6th token type to be TOKEN_WORD");
	cr_assert_eq(strcmp(world->value, "world"), 0,
		"Expected 6th token value to be 'world'");
	//
	ft_lstclear(&token_list, free_tok);
}
