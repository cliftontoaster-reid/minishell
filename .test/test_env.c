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

Test(env, standard_env, .init = cr_redirect_stdout)
{
	t_list	*envp;

	envp = NULL;
	b_setenv("PWD", "/home/test", &envp);
	b_setenv("USER", "test", &envp);
	b_setenv("HOME", "/home/test", &envp);
	ft_env(&envp);
	fflush(stdout);
	cr_assert_stdout_eq_str("PWD=/home/test\nUSER=test\nHOME=/home/test\n");
	ft_lstclear(&envp, free);
}

Test(env, empty_env, .init = cr_redirect_stderr)
{
	t_list	*envp;

	envp = NULL;
	ft_env(&envp);
	fflush(stderr);
	cr_assert_stderr_eq_str("env: no environment variables found\n");
	ft_lstclear(&envp, free);
}
