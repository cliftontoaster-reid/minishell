/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:25:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:26:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>

size_t	expand_special_var(char *dest, char c, size_t k, size_t len)
{
	if (c == '?')
		k += snprintf(&dest[k], len + 1, "%d", g_status_code);
	else if (c == '$')
		k += snprintf(&dest[k], len + 1, "%d", b_getpid());
	return (k);
}
