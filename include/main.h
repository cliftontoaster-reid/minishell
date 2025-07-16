/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:15:21 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "reader.h"
# include "shared.h"

// Shell initialization and cleanup
t_reader	*init_shell(char **envp);
void		cleanup_shell(t_reader *reader_ptr);

// Input handling
int			read_input(t_reader *reader_ptr);

// Variable expansion functions
void		build_varnames_array(t_reader *reader_ptr, t_varexp *varexp);
void		expand_command_variables(t_reader *reader_ptr, t_varexp *varexp);
void		process_variable_expansion(t_reader *reader_ptr);
void		free_varlists(t_list *varlists);

// Command processing
void		process_commands(t_reader *reader_ptr);

// Cleanup functions
void		cleanup_iteration(t_reader *reader_ptr);

#endif
