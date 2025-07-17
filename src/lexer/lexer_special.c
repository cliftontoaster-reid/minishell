/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:44:26 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/17 15:10:49 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <errno.h>

static t_token_type	get_special_type(const char *text, int pos, bool *special)
{
	if (text[pos] == '|')
		return (TOKEN_PIPE);
	if (text[pos] == '>')
	{
		if (text[pos + 1] == '>')
		{
			*special = true;
			return (TOKEN_REDIRECT_APPEND);
		}
		return (TOKEN_REDIRECT_OUT);
	}
	if (text[pos] == '<')
	{
		if (text[pos + 1] == '<')
		{
			*special = true;
			return (TOKEN_REDIRECT_HEREDOC);
		}
		return (TOKEN_REDIRECT_IN);
	}
	return (TOKEN_NONE);
}

static t_token	*make_special_token(const char *text, int pos, bool special,
		t_token_type type)
{
	t_token	*token;
	char	*substr;

	substr = ft_substr(text, pos, 1 + special);
	if (substr == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	token = create_token(substr, type);
	free(substr);
	if (token == NULL)
		errno = ENOMEM;
	return (token);
}

static t_list	*make_special_node(t_token *token)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (node == NULL)
	{
		free_token(token);
		errno = ENOMEM;
	}
	return (node);
}

void	lexer_special(t_lexer *lexer)
{
	bool			special;
	t_token_type	type;
	t_token			*token;
	t_list			*node;

	special = false;
	type = get_special_type(lexer->text, lexer->pos, &special);
	token = make_special_token(lexer->text, lexer->pos, special, type);
	if (token == NULL)
		return ;
	node = make_special_node(token);
	if (node == NULL)
		return ;
	ft_lstadd_back(&lexer->token_list, node);
	if (special)
		lexer->pos++;
	lexer->start = lexer->pos + 1;
}
