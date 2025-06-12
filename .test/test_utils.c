/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:01:29 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:21:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

// Helper function to find a specific environment variable in the list
t_env	*find_env_var(t_list *env_list, const char *key)
{
	t_list	*current;
	t_env	*env_data;

	current = env_list;
	while (current)
	{
		env_data = (t_env *)current->content;
		if (env_data && env_data->key && ft_strncmp(env_data->key, key,
				ft_strlen(key) + 1) == 0)
			return (env_data);
		current = current->next;
	}
	return (NULL);
}

// Helper function to properly free environment list
void	free_env_data(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (env)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
	}
}
