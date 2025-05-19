/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_soft_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:14 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/19 16:54:16 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shared.h"

bool	has_soft_redirect(t_command *cmd)
{
	if (cmd == NULL)
		return (false);
	return ((cmd->flags & FLAG_SOFT_REDIRECT) != 0);
}
