/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 16:00:55 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base_commands.h"
#include "shared.h"

int	export_with_value(const char *arg, t_list **envp)
{
	char	*key;
	char	*value;
	char	*equals_pos;
	int		key_len;

	equals_pos = ft_strchr(arg, '=');
	key_len = equals_pos - arg;
	key = ft_substr(arg, 0, key_len);
	if (!key)
		return (1);
	value = equals_pos + 1;
	b_setenv(key, value, envp);
	free(key);
	return (0);
}
