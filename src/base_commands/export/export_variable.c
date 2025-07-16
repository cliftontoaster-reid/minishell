/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 16:00:55 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base_commands.h"
#include "shared.h"
#include <unistd.h>

int	export_variable(const char *arg, t_list **envp)
{
	char	*equals_pos;

	if (!is_valid_identifier(arg))
	{
		write(2, "minishell: export: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	equals_pos = ft_strchr(arg, '=');
	if (equals_pos)
		return (export_with_value(arg, envp));
	return (export_without_value(arg, envp));
}
