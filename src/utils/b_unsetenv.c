/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unsetenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 15:00:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <stdlib.h>
#include <unistd.h>

void	b_unsetenv(const char *key, void (*del)(void *), t_list **envp)
{
	t_list	*current;
	t_list	*prev;

	if (!key || !envp || !*envp)
		return ;
	if (ft_strncmp(key, "PWD", 4) == 0)
		return (set_pwd_to_current_dir(key, envp));
	if (ft_strncmp(key, "OLDPWD", 7) == 0)
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
