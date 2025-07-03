/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:15:00 by creid             #+#    #+#             */
/*   Updated: 2025/07/03 16:15:00 by creid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "test_utils.h"
#include <criterion/redirect.h>

// Forward declaration for ft_env if it's not in a header included by test_utils.h
int	ft_env(t_list **env);

Test(env, standard_env, .init = cr_redirect_stdout)
{
	t_list	*envp;
	int		ret;

	envp = NULL;
	b_setenv("PWD", "/home/test", &envp);
	b_setenv("USER", "test", &envp);
	b_setenv("HOME", "/home/test", &envp);
	ret = ft_env(&envp);
	cr_assert_eq(ret, 0, "ft_env should return (0 on success");
	fflush(stdout);
	cr_assert_stdout_eq_str("PWD=/home/test\nUSER=test\nHOME=/home/test\n");
	ft_lstclear(&envp, free);
}

Test(env, empty_env, .init = cr_redirect_stderr)
{
	t_list	*envp;
	int		ret;

	envp = NULL;
	ret = ft_env(&envp);
	cr_assert_eq(ret, 1, "ft_env should return (1 when env is empty");
	fflush(stderr);
	cr_assert_stderr_eq_str("env: no environment variables found\n");
	ft_lstclear(&envp, free);
}
