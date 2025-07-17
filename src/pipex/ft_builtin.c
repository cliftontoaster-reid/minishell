/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:38:39 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/17 14:33:04 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

static void	is_builtin2(t_cmd *cmd, t_list **env, int cmd_idx)
{
	if (!ft_strncmp(cmd[cmd_idx].args[0], "pwd", 4))
	{
		ft_pwd(env);
		closefd(cmd, EXIT_SUCCESS, NULL);
	}
	if (!ft_strncmp(cmd[cmd_idx].args[0], "unset", 6))
	{
		ft_unset(cmd[cmd_idx].args, env);
		closefd(cmd, EXIT_SUCCESS, NULL);
	}
	if (!ft_strncmp(cmd[cmd_idx].args[0], "exit", 5))
	{
		ft_cleanup_cmd(cmd);
		ft_exit(cmd[cmd_idx].args, NULL);
		closefd(cmd, EXIT_SUCCESS, NULL);
	}
}

void	is_builtin(t_cmd *cmd, t_list **env, int cmd_idx)
{
	if (!ft_strncmp(cmd[cmd_idx].args[0], "cd", 3))
		closefd(cmd, EXIT_SUCCESS, NULL);
	if (!ft_strncmp(cmd[cmd_idx].args[0], "echo", 5))
	{
		ft_echo(cmd[cmd_idx].argc, cmd[cmd_idx].args);
		closefd(cmd, EXIT_SUCCESS, NULL);
	}
	if (!ft_strncmp(cmd[cmd_idx].args[0], "env", 4))
	{
		ft_env(env);
		closefd(cmd, EXIT_SUCCESS, NULL);
	}
	if (!ft_strncmp(cmd[cmd_idx].args[0], "export", 7))
	{
		ft_export(cmd[cmd_idx].args, env);
		closefd(cmd, EXIT_SUCCESS, NULL);
	}
	is_builtin2(cmd, env, cmd_idx);
}
