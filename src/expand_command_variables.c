/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command_variables.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:08:13 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "varextract.h"

void	expand_command_variables(t_reader *reader_ptr, t_varexp *varexp)
{
	int	ai;

	if (!reader_ptr->varnames)
		return ;
	ai = 0;
	while (reader_ptr->commands[varexp->cmd_idx].args[ai])
	{
		reader_ptr->commands[varexp->cmd_idx].args[ai] = ft_var(
			reader_ptr->commands[varexp->cmd_idx].args[ai],
			reader_ptr->varnames, reader_ptr->env);
		ai++;
	}
	free(reader_ptr->varnames);
	reader_ptr->varnames = NULL;
}
