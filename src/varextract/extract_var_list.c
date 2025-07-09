/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:37:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/09 15:19:05 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varextract.h"

static char	*extract_var_name(const char *value)
{
	const char	*dollar_pos;
	const char	*start;
	int			len;

	dollar_pos = ft_strchr(value, '$');
	if (dollar_pos != NULL && *(dollar_pos + 1))
	{
		start = dollar_pos + 1;
		len = 0;
		while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
			len++;
		if (len > 0)
			return (ft_substr(start, 0, len));
	}
	return (NULL);
}

static int	add_var_to_list(t_list **var_list, char *var_name)
{
	t_list	*new_node;

	new_node = ft_lstnew(var_name);
	if (new_node == NULL)
	{
		free(var_name);
		return (0);
	}
	ft_lstadd_back(var_list, new_node);
	printf("Added variable: %s\n", var_name);
	return (1);
}

static t_list	*extract_var_lists(t_list *tokens)
{
	t_list	*cmd_var_lists;
	t_list	*cur_var_list;
	t_token	*token;
	char	*var_name;
	t_list	*iter;

	cmd_var_lists = NULL;
	cur_var_list = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->type == TOKEN_PIPE)
		{
			ft_lstadd_back(&cmd_var_lists, ft_lstnew(cur_var_list));
			cur_var_list = NULL;
		}
		else if (token->type == TOKEN_WORD)
		{
			var_name = extract_var_name(token->value);
			if (var_name)
			{
				if (!add_var_to_list(&cur_var_list, var_name))
				{
					ft_lstclear(&cur_var_list, free);
					while (cmd_var_lists)
					{
						iter = cmd_var_lists->next;
						ft_lstclear((t_list **)&cmd_var_lists->content, free);
						free(cmd_var_lists);
						cmd_var_lists = iter;
					}
					errno = ENOMEM;
					return (NULL);
				}
			}
		}
		tokens = tokens->next;
	}
	ft_lstadd_back(&cmd_var_lists, ft_lstnew(cur_var_list));
	return (cmd_var_lists);
}

t_list	*b_varextract(t_list *tokens)
{
	if (!tokens)
		return (NULL);
	return (extract_var_lists(tokens));
}
