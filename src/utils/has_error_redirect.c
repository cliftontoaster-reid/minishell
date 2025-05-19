/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_error_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:52:21 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/19 16:53:31 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shared.h"

bool	has_error_redirect(t_command *cmd)
{
	if (cmd == NULL)
		return (false);
	return ((cmd->flags & FLAG_ERROR_REDIRECT) != 0);
}
