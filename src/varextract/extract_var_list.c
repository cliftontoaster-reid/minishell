/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:37:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/15 12:06:34 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varextract.h"

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
	t_list		*cmd_var_lists;
	t_list		*cur_var_list;
	t_token		*token;
	char		*var_name;
	t_list		*iter;
	const char	*p;
	const char	*start;
	int			len;

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
			/* Extract all variable names after each '$' in the token value */
			p = token->value;
			while ((p = ft_strchr(p, '$')))
			{
				if (*(p + 1) && (ft_isalnum(*(p + 1)) || *(p + 1) == '_'))
				{
					start = p + 1;
					len = 0;
					while (start[len] && (ft_isalnum(start[len])
							|| start[len] == '_'))
						len++;
					if (len > 0)
					{
						var_name = ft_substr(start, 0, len);
						if (!var_name)
						{
							/* Memory failure: cleanup and abort */
							ft_lstclear(&cur_var_list, free);
							while (cmd_var_lists)
							{
								iter = cmd_var_lists->next;
								ft_lstclear((t_list **)&cmd_var_lists->content,
									free);
								free(cmd_var_lists);
								cmd_var_lists = iter;
							}
							errno = ENOMEM;
							return (NULL);
						}
						/* Add to current variable list */
						if (!add_var_to_list(&cur_var_list, var_name))
						{
							/* add_var_to_list freed var_name on failure */
							ft_lstclear(&cur_var_list, free);
							while (cmd_var_lists)
							{
								iter = cmd_var_lists->next;
								ft_lstclear((t_list **)&cmd_var_lists->content,
									free);
								free(cmd_var_lists);
								cmd_var_lists = iter;
							}
							errno = ENOMEM;
							return (NULL);
						}
					}
				}
				p++;
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
