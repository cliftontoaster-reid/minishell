/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_var.c                               :+:      :+:    :+:   */
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

size_t	handle_special_var(char c)
{
	if (c == '?')
		return (num_places(g_status_code));
	if (c == '$')
		return (num_places(b_getpid()));
	return (0);
}
