/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/05 12:42:22 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

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

static t_env	*create_new_env_var(const char *key, const char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (!env->key)
	{
		free(env);
		return (NULL);
	}
	env->value = ft_strdup(value);
	if (!env->value)
	{
		free(env->key);
		free(env);
		return (NULL);
	}
	return (env);
}

static bool	update_existing_var(t_env *env_entry, const char *value)
{
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return (false);
	free(env_entry->value);
	env_entry->value = new_value;
	return (true);
}

static void	add_new_env_var(const char *key, const char *value, t_list **envp)
{
	t_env	*new_env;
	t_list	*new_node;

	new_env = create_new_env_var(key, value);
	if (!new_env)
		return ;
	new_node = ft_lstnew(new_env);
	if (!new_node)
	{
		free(new_env->key);
		free(new_env->value);
		free(new_env);
		return ;
	}
	ft_lstadd_back(envp, new_node);
}

void	b_setenv(const char *key, const char *value, t_list *envp)
{
	t_list	*current;
	t_env	*env_entry;

	if (!key || !value || !envp)
		return ;
	current = envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (env_entry && env_entry->key && str_equal(env_entry->key, key))
		{
			update_existing_var(env_entry, value);
			return ;
		}
		current = current->next;
	}
	add_new_env_var(key, value, &envp);
}
