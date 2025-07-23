/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 17:58:11 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <stdlib.h>

static void	free_env_var(t_env *env_var)
{
	if (env_var->key)
		free(env_var->key);
	if (env_var->value)
		free(env_var->value);
	free(env_var);
}

void	add_new_env_var(const char *key, const char *value, t_list **envp)
{
	t_env	*new_env;
	t_list	*new_node;

	if (!key || !value || !envp)
		return ;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	if (!new_env->key || !new_env->value)
	{
		return (free_env_var(new_env));
	}
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
