/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_matching_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 15:01:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	is_matching_env(t_list *node, const char *key)
{
	t_env	*env_entry;

	if (!node || !node->content)
		return (0);
	env_entry = (t_env *)node->content;
	if (!env_entry || !env_entry->key)
		return (0);
	return (str_equal(env_entry->key, key));
}
