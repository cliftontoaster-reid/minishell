/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_getenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/20 15:29:08 by lfiorell@st      ###   ########.fr       */
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

char	*b_getenv(const char *key, t_list *envp)
{
	t_list	*current;
	t_env	*env_entry;

	if (!key || !envp)
	{
		errno = EINVAL;
		return (NULL);
	}
	current = envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (env_entry && env_entry->key && str_equal(env_entry->key, key))
		{
			if (env_entry->value)
				return (ft_strdup(env_entry->value));
			return (NULL);
		}
		current = current->next;
	}
	return (NULL);
}
