/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:21:36 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/09 11:16:38 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <unistd.h>

static void	freeenv(void *env)
{
	t_env	*env_var;

	if (env)
	{
		env_var = (t_env *)env;
		if (env_var->key)
			free(env_var->key);
		if (env_var->value)
			free(env_var->value);
		free(env_var);
	}
}

static int	is_valid_identifiir(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(char **args, t_list **envp)
{
	int	i;
	int	exit_status;

	if (!args || !envp)
	{
		g_status_code = 0;
		return ;
	}
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (is_valid_identifiir(args[i]))
		{
			b_unsetenv(args[i], freeenv, envp);
		}
		else
		{
			write(2, "minishell: unset: `", 19);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 26);
			exit_status = 1;
		}
		i++;
	}
	g_status_code = exit_status;
}
