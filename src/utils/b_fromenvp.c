/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_fromenvp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:00:57 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/06 14:58:18 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include <errno.h>

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static t_env	*create_env_entry(char *key, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
	{
		errno = ENOMEM;
		return (NULL);
	}
	env->key = ft_strdup(key);
	if (!env->key)
	{
		free(env);
		errno = ENOMEM;
		return (NULL);
	}
	env->value = ft_strdup(value);
	if (!env->value)
	{
		free(env->key);
		free(env);
		errno = ENOMEM;
		return (NULL);
	}
	return (env);
}

static int	parse_env_string(char *env_str, char **key, char **value)
{
	char	*equals_pos;

	equals_pos = ft_strchr(env_str, '=');
	if (!equals_pos)
		return (0);
	*key = ft_substr(env_str, 0, equals_pos - env_str);
	if (!*key)
	{
		errno = ENOMEM;
		return (0);
	}
	if (ft_strlen(*key) == 0)
	{
		free(*key);
		errno = EINVAL;
		return (0);
	}
	*value = ft_strdup(equals_pos + 1);
	if (!*value)
	{
		free(*key);
		errno = ENOMEM;
		return (0);
	}
	return (1);
}

static int	process_env_entry(char *env_str, t_list **env_list)
{
	char	*key;
	char	*value;
	t_env	*env;

	if (!parse_env_string(env_str, &key, &value))
		return (0);
	env = create_env_entry(key, value);
	free(key);
	free(value);
	if (!env)
	{
		errno = ENOMEM;
		return (0);
	}
	ft_lstadd_back(env_list, ft_lstnew(env));
	return (1);
}

t_list	*b_fromenvp(char *const *envp)
{
	t_list	*env_list;

	env_list = NULL;
	while (*envp)
	{
		if (!process_env_entry(*envp, &env_list))
		{
			ft_lstclear(&env_list, free);
			return (NULL);
		}
		envp++;
	}
	return (env_list);
}
