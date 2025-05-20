/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:14:25 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/20 12:08:14 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static void	freerf(void *token)
{
	free_token((t_token *)token);
}

static void	try_join(t_list *token)
{
	t_token	*current;
	t_token	*next;
	t_token	*new_token;
	t_list	*del;

	if (!token || !token->next || !token->content || !token->next->content)
		return ;
	current = token->content;
	next = token->next->content;
	if (current->type != TOKEN_WORD || next->type != TOKEN_WORD)
		return ;
	new_token = create_token(ft_strjoin(current->value, next->value),
			TOKEN_WORD);
	if (!new_token)
		return ;
	{
		del = token->next;
		token->content = new_token;
		token->next = del->next;
		ft_lstdelone(del, freerf);
		free_token(current);
	}
	try_join(token);
}

void	join_words(t_lexer *lexer)
{
	t_list *token;

	token = lexer->token_list;
	while (token)
	{
		try_join(token);
		token = token->next;
	}
}