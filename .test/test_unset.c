/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creid <creid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:30:00 by creid             #+#    #+#             */
/*   Updated: 2025/07/03 16:30:00 by creid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "test_utils.h"
#include <criterion/redirect.h>

Test(unset, single_valid_var)
{
	t_list	*envp;
	char	*args[] = {"unset", "USER", NULL};

	envp = NULL;
	b_setenv("USER", "test", &envp);
	ft_unset(args, &envp);
	cr_assert_null(b_getenv("USER", envp), "USER should be unset");
	ft_lstclear(&envp, free);
}

Test(unset, multiple_valid_vars)
{
	t_list	*envp;
	char	*args[] = {"unset", "USER", "PWD", NULL};

	envp = NULL;
	b_setenv("USER", "test", &envp);
	b_setenv("PWD", "/home/test", &envp);
	ft_unset(args, &envp);
	cr_assert_null(b_getenv("USER", envp), "USER should be unset");
	cr_assert_not_null(b_getenv("PWD", envp), "PWD should still exist");
	ft_lstclear(&envp, free);
}

Test(unset, unset_nonexistent_var)
{
	t_list	*envp;
	char	*args[] = {"unset", "DOESNOTEXIST", NULL};

	envp = NULL;
	b_setenv("USER", "test", &envp);
	ft_unset(args, &envp);
	cr_assert_not_null(b_getenv("USER", envp), "USER should still exist");
	ft_lstclear(&envp, free);
}

Test(unset, invalid_identifier, .init = cr_redirect_stderr)
{
	t_list	*envp;
	char	*args[] = {"unset", "1INVALID", NULL};

	envp = NULL;
	b_setenv("USER", "test", &envp);
	ft_unset(args, &envp);
	fflush(stderr);
	cr_assert_stderr_eq_str("minishell: unset: `1INVALID': not a valid identifier\n");
	cr_assert_not_null(b_getenv("USER", envp), "USER should still exist");
	ft_lstclear(&envp, free);
}

Test(unset, no_arguments)
{
	t_list	*envp;
	char	*args[] = {"unset", NULL};

	envp = NULL;
	b_setenv("USER", "test", &envp);
	ft_unset(args, &envp);
	cr_assert_not_null(b_getenv("USER", envp), "USER should still exist");
	ft_lstclear(&envp, free);
}

Test(unset, prefix_var)
{
	t_list	*envp;
	char	*args[] = {"unset", "USER", NULL};

	envp = NULL;
	b_setenv("USER", "test", &envp);
	b_setenv("USERNAME", "tester", &envp);
	ft_unset(args, &envp);
	cr_assert_null(b_getenv("USER", envp), "USER should be unset");
	cr_assert_not_null(b_getenv("USERNAME", envp),
		"USERNAME should still exist");
	ft_lstclear(&envp, free);
}
