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

// Forward declaration for ft_unset if not in a header
int	ft_unset(char **args, t_list **envp);

Test(unset, single_valid_var)
{
	t_list	*envp;
	char	*args[] = {"unset", "USER", NULL};
	int		ret;

	envp = NULL;
	b_setenv("USER", "test", &envp);
	ret = ft_unset(args, &envp);
	cr_assert_eq(ret, 0, "ft_unset should return (0 on success");
	cr_assert_null(b_getenv("USER", envp), "USER should be unset");
	ft_lstclear(&envp, free);
}

Test(unset, multiple_valid_vars)
{
	t_list	*envp;
	char	*args[] = {"unset", "USER", "PWD", NULL};
	int		ret;

	envp = NULL;
	b_setenv("USER", "test", &envp);
	b_setenv("PWD", "/home/test", &envp);
	ret = ft_unset(args, &envp);
	cr_assert_eq(ret, 0, "ft_unset should return (0 on success");
	cr_assert_null(b_getenv("USER", envp), "USER should be unset");
	cr_assert_null(b_getenv("PWD", envp), "PWD should be unset");
	ft_lstclear(&envp, free);
}

Test(unset, unset_nonexistent_var)
{
	t_list	*envp;
	char	*args[] = {"unset", "DOESNOTEXIST", NULL};
	int		ret;

	envp = NULL;
	b_setenv("USER", "test", &envp);
	ret = ft_unset(args, &envp);
	cr_assert_eq(ret, 0,
		"ft_unset should return (0 even if var does not exist");
	cr_assert_not_null(b_getenv("USER", envp), "USER should still exist");
	ft_lstclear(&envp, free);
}

Test(unset, invalid_identifier, .init = cr_redirect_stderr)
{
	t_list	*envp;
	char	*args[] = {"unset", "1INVALID", NULL};
	int		ret;

	envp = NULL;
	b_setenv("USER", "test", &envp);
	ret = ft_unset(args, &envp);
	cr_assert_eq(ret, 1, "ft_unset should return (1 for invalid identifier");
	fflush(stderr);
	cr_assert_stderr_eq_str("minishell: unset: `1INVALID': not a valid identifier\n");
	cr_assert_not_null(b_getenv("USER", envp), "USER should still exist");
	ft_lstclear(&envp, free);
}

Test(unset, no_arguments)
{
	t_list	*envp;
	char	*args[] = {"unset", NULL};
	int		ret;

	envp = NULL;
	b_setenv("USER", "test", &envp);
	ret = ft_unset(args, &envp);
	cr_assert_eq(ret, 0, "ft_unset should return (0 when no arguments");
	cr_assert_not_null(b_getenv("USER", envp), "USER should still exist");
	ft_lstclear(&envp, free);
}

Test(unset, prefix_var)
{
	t_list	*envp;
	char	*args[] = {"unset", "USER", NULL};
	int		ret;

	envp = NULL;
	b_setenv("USER", "test", &envp);
	b_setenv("USERNAME", "tester", &envp);
	ret = ft_unset(args, &envp);
	cr_assert_eq(ret, 0, "ft_unset should return (0 on success");
	cr_assert_null(b_getenv("USER", envp), "USER should be unset");
	cr_assert_not_null(b_getenv("USERNAME", envp),
		"USERNAME should still exist");
	ft_lstclear(&envp, free);
}
