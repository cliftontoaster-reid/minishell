/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:38:39 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/21 15:56:51 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

void	is_builtin(t_cmd **cmd, t_list **env, int cmd_idx, t_reader *exit)
{
	if (!ft_strncmp((*cmd)[cmd_idx].args[0], "cd", 3))
		closefd(*cmd, EXIT_SUCCESS, exit);
	else if (!ft_strncmp((*cmd)[cmd_idx].args[0], "echo", 5))
		ft_echo((*cmd)[cmd_idx].argc, (*cmd)[cmd_idx].args);
	else if (!ft_strncmp((*cmd)[cmd_idx].args[0], "env", 4))
		ft_env(env);
	else if (!ft_strncmp((*cmd)[cmd_idx].args[0], "export", 7))
		ft_export((*cmd)[cmd_idx].args, env);
	else if (!ft_strncmp((*cmd)[cmd_idx].args[0], "pwd", 4))
		ft_pwd(env);
	else if (!ft_strncmp((*cmd)[cmd_idx].args[0], "unset", 6))
		ft_unset((*cmd)[cmd_idx].args, env);
	else if (!ft_strncmp((*cmd)[cmd_idx].args[0], "exit", 5))
		ft_exit((*cmd)[cmd_idx].args, exit, cmd);
	closefd(*cmd, EXIT_SUCCESS, exit);
}
