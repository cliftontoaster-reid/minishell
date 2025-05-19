/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_pipe_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/19 16:54:03 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shared.h"

bool	has_pipe_in(t_command *cmd)
{
	if (cmd == NULL)
		return (false);
	return ((cmd->flags & FLAG_PIPE_IN) != 0);
}
