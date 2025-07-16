/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_commands.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:10:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 16:00:55 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_COMMANDS_H
# define BASE_COMMANDS_H

# include "shared.h"
# include <unistd.h>

int		is_valid_identifier(const char *str);
void	print_exported_vars(t_list *envp);
int		export_with_value(const char *arg, t_list **envp);
int		export_without_value(const char *arg, t_list **envp);
int		export_variable(const char *arg, t_list **envp);

#endif
