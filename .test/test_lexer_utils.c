/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:27:25 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
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
