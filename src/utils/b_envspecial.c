/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_envspecial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@student.42.fr>             +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:00:00 by copilot          #+#    #+#             */
/*   Updated: 2025/07/23 21:00:00 by copilot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <errno.h>

/**
 * @brief Handle special environment variables after parsing.
 *        Currently increments SHLVL if present.
 * @param key   Environment variable name
 * @param value Pointer to the variable value string (will be freed & replaced)
 */
void	b_envspecial(char *key, char **value)
{
	int		lvl;
	char	*new_val;

	if (str_equal(key, "SHLVL") == 0)
	{
		lvl = ft_atoi(*value);
		new_val = ft_itoa(lvl + 1);
		if (new_val)
		{
			free(*value);
			*value = new_val;
		}
		else
		{
			errno = ENOMEM;
		}
	}
}
