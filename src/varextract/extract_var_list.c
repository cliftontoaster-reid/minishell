/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:37:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:12:56 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varextract.h"

static int add_var_to_list(t_list **var_list, char *var_name) {
  t_list *new_node;

  new_node = ft_lstnew(var_name);
  if (new_node == NULL) {
    free(var_name);
    return (0);
  }
  ft_lstadd_back(var_list, new_node);
  return (1);
}

static t_list *cleanup_var_lists(t_list *cmd_var_lists, t_list *cur_var_list) {
  t_list *iter;

  ft_lstclear(&cur_var_list, free);
  while (cmd_var_lists) {
    iter = cmd_var_lists->next;
    ft_lstclear((t_list **)&cmd_var_lists->content, free);
    free(cmd_var_lists);
    cmd_var_lists = iter;
  }
  return (NULL);
}

static int handle_variable(const char *start, t_list **cur_var_list) {
  char *var_name;
  int len;

  len = 0;
  while (ft_isalnum(start[len]) || start[len] == '_')
    len++;
  var_name = ft_substr(start, 0, len);
  if (!var_name || !add_var_to_list(cur_var_list, var_name)) {
    free(var_name);
    return (0);
  }
  return (1);
}

static int extract_vars_from_word(const char *value, t_list **cur_var_list,
                                  t_list **cmd_var_lists) {
  const char *p;
  const char *next_dollar;

  p = value;
  next_dollar = ft_strchr(p, '$');
  while (next_dollar) {
    if (*(next_dollar + 1) &&
        (ft_isalnum(*(next_dollar + 1)) || *(next_dollar + 1) == '_')) {
      if (!handle_variable(next_dollar + 1, cur_var_list)) {
        cleanup_var_lists(*cmd_var_lists, *cur_var_list);
        errno = ENOMEM;
        return (-1);
      }
    }
    p = next_dollar + 1;
    next_dollar = ft_strchr(p, '$');
  }
  return (0);
}

t_list *b_varextract(t_list *tokens) {
  t_list *cmd_var_lists;
  t_list *cur_var_list;
  t_token *token;

  cmd_var_lists = NULL;
  cur_var_list = NULL;
  while (tokens) {
    token = (t_token *)tokens->content;
    if (token->type == TOKEN_PIPE) {
      ft_lstadd_back(&cmd_var_lists, ft_lstnew(cur_var_list));
      cur_var_list = NULL;
    } else if (token->type == TOKEN_WORD) {
      if (extract_vars_from_word(token->value, &cur_var_list, &cmd_var_lists) <
          0)
        return (NULL);
    }
    tokens = tokens->next;
  }
  ft_lstadd_back(&cmd_var_lists, ft_lstnew(cur_var_list));
  return (cmd_var_lists);
}
