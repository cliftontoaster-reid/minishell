/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unsetenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/22 13:41:31 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <stdlib.h>

static int	str_equal(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (0);
	return (ft_strncmp(s1, s2, len1) == 0);
}

static void	free_env_entry(void *content)
{
	t_env	*env;

	if (!content)
		return ;
	env = (t_env *)content;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

static void	remove_env_node(t_list *prev, t_list *current, t_list **envp,
		void (*del)(void *))
{
	if (prev)
		prev->next = current->next;
	else
		*envp = current->next;
	if (del)
		del(current->content);
	else
		free_env_entry(current->content);
	free(current);
}

static int	is_matching_env(t_list *node, const char *key)
{
	t_env	*env_entry;

	if (!node || !node->content)
		return (0);
	env_entry = (t_env *)node->content;
	if (!env_entry || !env_entry->key)
		return (0);
	return (str_equal(env_entry->key, key));
}

void	b_unsetenv(const char *key, void (*del)(void *), t_list **envp)
{
	t_list	*current;
	t_list	*prev;

	if (!key || !envp || !*envp)
		return ;
	if (ft_strncmp(key, "PWD", 4) == 0 || ft_strncmp(key, "OLDPWD", 7) == 0)
		return (b_setenv(key, getenv(key), envp));
	current = *envp;
	prev = NULL;
	while (current)
	{
		if (is_matching_env(current, key))
		{
			remove_env_node(prev, current, envp, del);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
