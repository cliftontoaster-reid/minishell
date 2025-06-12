/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_get_command_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:49:41 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/10 13:41:46 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <errno.h>
#include <stddef.h>
#include <string.h>

// Stub for unimplemented built-ins: sets errno and returns NULL
static int	*cmd_not_implemented(struct s_builtin *ctx)
{
	(void)ctx;
	errno = ENOSYS;
	g_status_code = ENOSYS;
	return (NULL);
}

#define CMD_BUILTIN_NOT_IMPLEMENTED cmd_not_implemented
#define CMD_CD "cd"
#define CMD_EXIT "exit"
#define CMD_ENV "env"
#define CMD_EXPORT "export"
#define CMD_UNSET "unset"
#define CMD_PWD "pwd"
#define CMD_ECHO "echo"

t_cmd_func	b_get_command_func(const char *cmd)
{
	t_cmd_func	func;

	if (!cmd)
	{
		errno = EINVAL;
		return (NULL);
	}
	func = NULL;
	if (strcmp(cmd, CMD_CD) == 0)
		func = CMD_BUILTIN_NOT_IMPLEMENTED;
	else if (strcmp(cmd, CMD_EXIT) == 0)
		func = CMD_BUILTIN_NOT_IMPLEMENTED;
	else if (strcmp(cmd, CMD_ENV) == 0)
		func = CMD_BUILTIN_NOT_IMPLEMENTED;
	else if (strcmp(cmd, CMD_EXPORT) == 0)
		func = CMD_BUILTIN_NOT_IMPLEMENTED;
	else if (strcmp(cmd, CMD_UNSET) == 0)
		func = CMD_BUILTIN_NOT_IMPLEMENTED;
	else if (strcmp(cmd, CMD_PWD) == 0)
		func = CMD_BUILTIN_NOT_IMPLEMENTED;
	else if (strcmp(cmd, CMD_ECHO) == 0)
		func = CMD_BUILTIN_NOT_IMPLEMENTED;
	if (func == NULL)
		errno = EINVAL;
	return (func);
}
