/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_output_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:53:51 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/19 16:53:54 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shared.h"

bool	has_output_redirect(t_command *cmd)
{
	if (cmd == NULL)
		return (false);
	return ((cmd->flags & FLAG_OUTPUT_REDIRECT) != 0);
}
