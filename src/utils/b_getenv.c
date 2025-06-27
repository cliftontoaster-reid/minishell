/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_getenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/27 19:01:33 by lfiorell@st      ###   ########.fr       */
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

static char	*ft_strjoin_free(char *s1, char *s2, int free_s1)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		result = ft_strdup(s2);
		free(s2);
	}
	else if (!s2)
	{
		result = ft_strdup(s1);
		free(s1);
	}
	else
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		result = ft_calloc(len1 + len2 + 1, sizeof(char));
		if (!result)
		{
			free(s1);
			free(s2);
			return (NULL);
		}
		ft_strlcpy(result, s1, len1 + 1);
		ft_strlcat(result, s2, len1 + len2 + 1);
		if (free_s1)
			free(s1);
		free(s2);
	}
	return (result);
}

static char	*format_env_entry(t_env *env_entry)
{
	char	*temp;
	char	*result;

	if (env_entry->value)
	{
		temp = ft_strjoin(env_entry->key, "=");
		result = ft_strjoin_free(temp, env_entry->value, 1);
		return (result);
	}
	else
		return (ft_strjoin(env_entry->key, "="));
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
