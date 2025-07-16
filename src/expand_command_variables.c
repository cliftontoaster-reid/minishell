/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command_variables.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:18:07 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "varextract.h"

void	expand_command_variables(t_reader *reader_ptr, t_varexp *varexp)
{
	int		ai;
	char	**args;

	if (!reader_ptr->varnames)
		return ;
	ai = 0;
	args = reader_ptr->commands[varexp->cmd_idx].args;
	while (args[ai])
	{
		args[ai] = ft_var(args[ai], reader_ptr->varnames, reader_ptr->env);
		ai++;
	}
	free(reader_ptr->varnames);
	reader_ptr->varnames = NULL;
}
