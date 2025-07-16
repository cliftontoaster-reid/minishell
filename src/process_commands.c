/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:15:21 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "main_extra.h"
#include "parser.h"
#include "pipex.h"
#include "shared.h"
#include "utils.h"

void	process_commands(t_reader *reader_ptr)
{
	t_list	*varlists;

	reader_ptr->commands = parser_to_list(reader_ptr->parser);
	varlists = reader_ptr->vars;
	process_variable_expansion(reader_ptr);
	free_varlists(varlists);
	if (reader_ptr->commands)
		process_heredocs(reader_ptr->commands, reader_ptr->env);
	reader_ptr->commands = remove_empty_commands(reader_ptr->commands);
	ft_pipex(reader_ptr->commands, reader_ptr->env, reader_ptr);
}
