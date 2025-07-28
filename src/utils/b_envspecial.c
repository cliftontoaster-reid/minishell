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

#include "utils.h"

/**
 * @brief Handle special environment variables after parsing.
 *        Currently increments SHLVL if present.
 * @param key   Environment variable name
 * @param value Pointer to the variable value string (will be freed & replaced)
 */
void	b_envspecial(char *key, char **value)
{
	(void)key;
	(void)value;
}
