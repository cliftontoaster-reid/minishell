/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:14:25 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/03 11:37:37 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static void	freerf(void *token)
{
	free_token((t_token *)token);
}

static bool	is_joinable_token(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TOKEN_WORD)
		return (true);
	if (token->type == TOKEN_NONE && token->value
		&& ft_strlen(token->value) == 0)
		return (true);
	return (false);
}

static char	*get_joined_value(t_token *current, t_token *next)
{
	if (current->type == TOKEN_NONE && ft_strlen(current->value) == 0)
		return (ft_strdup(next->value));
	else if (next->type == TOKEN_NONE && ft_strlen(next->value) == 0)
		return (ft_strdup(current->value));
	else
		return (ft_strjoin(current->value, next->value));
}

static void	try_join(t_list *token)
{
	t_token	*current;
	t_token	*next;
	t_token	*new_token;
	t_list	*del;
	char	*joined_value;

	if (!token || !token->next || !token->content || !token->next->content)
		return ;
	current = token->content;
	next = token->next->content;
	if (!is_joinable_token(current) || !is_joinable_token(next))
		return ;
	joined_value = get_joined_value(current, next);
	new_token = create_token(joined_value, TOKEN_WORD);
	if (!new_token)
		return ;
	del = token->next;
	token->content = new_token;
	token->next = del->next;
	ft_lstdelone(del, freerf);
	free_token(current);
	try_join(token);
}

void	join_words(t_lexer *lexer)
{
	t_list	*token;

	token = lexer->token_list;
	while (token)
	{
		try_join(token);
		token = token->next;
	}
}
