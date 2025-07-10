/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:00 by copilot           #+#    #+#             */
/*   Updated: 2025/07/03 17:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif
#include <limits.h>

Test(pwd, prints_current_directory, .init = cr_redirect_stdout)
{
	t_list	*envp;
	char	cwd[PATH_MAX];
	char	expected[PATH_MAX + 2];

	envp = NULL;
	getcwd(cwd, sizeof(cwd));
	b_setenv("PWD", cwd, &envp);
	ft_pwd(&envp);
	fflush(stdout);
	snprintf(expected, sizeof(expected), "%s\n", cwd);
	cr_assert_stdout_eq_str(expected);
	ft_lstclear(&envp, free);
}

Test(pwd, missing_pwd_env, .init = cr_redirect_stderr)
{
	t_list	*envp;

	envp = NULL;
	ft_pwd(&envp);
	fflush(stderr);
	cr_assert_stderr_eq_str("pwd: error retrieving current directory\n");
	ft_lstclear(&envp, free);
}

Test(pwd, empty_pwd_env, .init = cr_redirect_stdout)
{
	t_list	*envp;

	envp = NULL;
	b_setenv("PWD", "", &envp);
	ft_pwd(&envp);
	fflush(stdout);
	cr_assert_stdout_eq_str("\n");
	ft_lstclear(&envp, free);
}
