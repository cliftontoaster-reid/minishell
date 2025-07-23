/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_varexists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/06 15:00:46 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include "utils.h"
#include <errno.h>

bool	b_varexists(const char *key, t_list *envp)
{
	t_list	*current;
	t_env	*env_entry;

	if (!key || !envp)
	{
		errno = EINVAL;
		return (false);
	}
	current = envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (env_entry && env_entry->key && str_equal(env_entry->key, key))
			return (true);
		current = current->next;
	}
	return (false);
}
