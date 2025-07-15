/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:55:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/15 16:21:46 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <unistd.h>

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_exported_vars(t_list *envp)
{
	char	**env_vars;
	int		i;

	if (!envp)
		return ;
	env_vars = b_getenv(NULL, envp);
	if (!env_vars)
		return ;
	i = 0;
	while (env_vars[i])
	{
		write(1, "declare -x ", 11);
		write(1, env_vars[i], ft_strlen(env_vars[i]));
		write(1, "\n", 1);
		free(env_vars[i]);
		i++;
	}
	free(env_vars);
}

static int	export_with_value(const char *arg, t_list **envp)
{
	char	*key;
	char	*value;
	char	*equals_pos;
	int		key_len;

	equals_pos = ft_strchr(arg, '=');
	key_len = equals_pos - arg;
	key = ft_substr(arg, 0, key_len);
	if (!key)
		return (1);
	value = equals_pos + 1;
	b_setenv(key, value, envp);
	free(key);
	return (0);
}

static int	export_without_value(const char *arg, t_list **envp)
{
	char	*key;

	key = ft_strdup(arg);
	if (!key)
		return (1);
	b_setenv(key, "", envp);
	free(key);
	return (0);
}

static int	export_variable(const char *arg, t_list **envp)
{
	char	*equals_pos;

	if (!is_valid_identifier(arg))
	{
		write(2, "minishell: export: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	equals_pos = ft_strchr(arg, '=');
	if (equals_pos)
		return (export_with_value(arg, envp));
	return (export_without_value(arg, envp));
}

void	ft_export(char **argv, t_list **envp)
{
	int	i;
	int	exit_status;

	if (!argv || !envp)
	{
		g_status_code = 1;
		return ;
	}
	if (!argv[1])
	{
		if (envp && *envp)
			print_exported_vars(*envp);
		g_status_code = 0;
		return ;
	}
	exit_status = 0;
	i = 1;
	while (argv[i])
	{
		if (export_variable(argv[i], envp) != 0)
			exit_status = 1;
		i++;
	}
	g_status_code = exit_status;
}
