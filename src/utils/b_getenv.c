/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_getenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/15 15:59:25 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include <errno.h>

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

static char	*format_env_entry(t_env *env_entry)
{
	char	*result;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(env_entry->key);
	if (env_entry->value)
		value_len = ft_strlen(env_entry->value);
	else
		value_len = 0;
	result = malloc(key_len + value_len + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, env_entry->key, key_len + 1);
	ft_strlcat(result, "=", key_len + 2);
	if (env_entry->value)
		ft_strlcat(result, env_entry->value, key_len + value_len + 2);
	return (result);
}

static char	**get_all_env(t_list *envp)
{
	t_list	*current;
	t_env	*env_entry;
	char	**result;
	int		count;
	int		i;

	count = ft_lstsize(envp);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	current = envp;
	i = 0;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (env_entry && env_entry->key)
			result[i++] = format_env_entry(env_entry);
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

static char	**get_single_env(const char *key, t_list *envp)
{
	t_list	*current;
	t_env	*env_entry;
	char	**result;

	current = envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (env_entry && env_entry->key && str_equal(env_entry->key, key))
		{
			result = malloc(sizeof(char *) * 2);
			if (!result)
				return (NULL);
			if (env_entry->value)
				result[0] = ft_strdup(env_entry->value);
			else
				result[0] = ft_strdup("");
			result[1] = NULL;
			return (result);
		}
		current = current->next;
	}
	return (NULL);
}

char	**b_getenv(const char *key, t_list *envp)
{
	if (!envp)
	{
		errno = EINVAL;
		return (NULL);
	}
	if (!key)
		return (get_all_env(envp));
	return (get_single_env(key, envp));
}
