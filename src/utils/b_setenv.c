/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 15:02:08 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include "utils.h"
#include <errno.h>

void	b_setenv(const char *key, const char *value, t_list **envp)
{
	t_list	*current;
	t_env	*env_entry;

	if (!key || !value || !envp)
		return ;
	current = *envp;
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
	add_new_env_var(key, value, envp);
}
