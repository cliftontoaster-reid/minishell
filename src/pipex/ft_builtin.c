/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:38:39 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/07 15:21:30 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

void is_builtin(t_cmd *cmd, t_list **env, int cmd_idx)
{
	if (!ft_strncmp(cmd[cmd_idx].args[0], "cd", 2))
		closefd(cmd, EXIT_SUCCESS);
	if (!ft_strncmp(cmd[cmd_idx].args[0], "echo", 4))
	{
		ft_echo(cmd[cmd_idx].argc, cmd[cmd_idx].args);
		closefd(cmd, EXIT_SUCCESS);
	}
	if (!ft_strncmp(cmd[cmd_idx].args[0], "env", 3))
	{	
		ft_env(env);
		closefd(cmd, EXIT_SUCCESS);
	}
	if (!ft_strncmp(cmd[cmd_idx].args[0], "exit", 4))
	{
		ft_exit(cmd[cmd_idx].args, NULL);
		closefd(cmd, EXIT_SUCCESS);
	}
	if (!ft_strncmp(cmd[cmd_idx].args[0], "export", 6))
	{
		ft_export(cmd[cmd_idx].args, env);
		closefd(cmd, EXIT_SUCCESS);
	}
	if (!ft_strncmp(cmd[cmd_idx].args[0], "pwd", 3))
	{
		ft_pwd(env);
		closefd(cmd, EXIT_SUCCESS);
	}
	if (!ft_strncmp(cmd[cmd_idx].args[0], "unset", 5))
	{
		ft_unset(cmd[cmd_idx].args, env);
		closefd(cmd, EXIT_SUCCESS);
	}
}
