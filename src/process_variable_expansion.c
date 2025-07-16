/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variable_expansion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:08:13 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "main.h"

void	process_variable_expansion(t_reader *reader_ptr)
{
	t_list		*varlists;
	t_varexp	varexp;

	varlists = reader_ptr->vars;
	varexp.vl_node = varlists;
	varexp.cmd_idx = 0;
	while (varexp.vl_node && reader_ptr->commands[varexp.cmd_idx].args
		&& reader_ptr->commands[varexp.cmd_idx].argc)
	{
		build_varnames_array(reader_ptr, &varexp);
		expand_command_variables(reader_ptr, &varexp);
		varexp.vl_node = varexp.vl_node->next;
		varexp.cmd_idx++;
	}
}
