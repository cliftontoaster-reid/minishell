/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_existing_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 15:00:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <stdlib.h>

void	update_existing_var(t_env *env_entry, const char *value)
{
	if (!env_entry || !value)
		return ;
	if (env_entry->value)
		free(env_entry->value);
	env_entry->value = ft_strdup(value);
}
