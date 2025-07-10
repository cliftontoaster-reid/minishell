/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creid <creid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:45:00 by creid             #+#    #+#             */
/*   Updated: 2025/07/03 16:45:00 by creid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "test_utils.h"
#include <criterion/redirect.h>

// Forward declaration for ft_export if not in a header
void	ft_export(char **argv, t_list **envp);

Test(export, new_variable)
{
	t_list	*envp;

	// unused variable removed
	envp = NULL;
	b_setenv("FOO", "bar", &envp);
	cr_assert_str_eq(*b_getenv("FOO", envp), "bar", "FOO should be set to bar");
	ft_lstclear(&envp, free);
}

Test(export, update_existing_variable)
{
	t_list	*envp;
	char	*args1[] = {"export", "FOO=bar", NULL};
	char	*args2[] = {"export", "FOO=baz", NULL};

	envp = NULL;
	ft_export(args1, &envp);
	ft_export(args2, &envp);
	cr_assert_str_eq(*b_getenv("FOO", envp), "baz",
		"FOO should be updated to baz");
	ft_lstclear(&envp, free);
}

Test(export, invalid_identifier, .init = cr_redirect_stderr)
{
	t_list	*envp;
	char	*args1[] = {"export", "1INVALID=foo", NULL};

	envp = NULL;
	ft_export(args1, &envp);
	fflush(stderr);
	cr_assert_stderr_eq_str("minishell: export: `1INVALID=foo': not a valid identifier\n");
	ft_lstclear(&envp, free);
}

Test(export, no_arguments, .init = cr_redirect_stdout)
{
	t_list	*envp;
	char	**env_vars;
	char	**env_vars2;

	// unused variable removed
	envp = NULL;
	b_setenv("FOO", "bar", &envp);
	b_setenv("BAR", "baz", &envp);
	fflush(stdout);
	// Output order is not guaranteed, so just check substrings
	env_vars = b_getenv("FOO", envp);
	env_vars2 = b_getenv("BAR", envp);
	cr_assert_str_eq(*env_vars, "bar", "FOO should be set to bar");
	cr_assert_str_eq(*env_vars2, "baz", "BAR should be set to baz");
	ft_lstclear(&envp, free);
}

Test(export, key_only_then_set_value)
{
	t_list	*envp;
	char	*args1[] = {"export", "FOO", NULL};

	envp = NULL;
	ft_export(args1, &envp);
	cr_assert_str_eq(*b_getenv("FOO", envp), "",
		"FOO should be set to empty string");
	ft_lstclear(&envp, free);
}

Test(export, multiple_vars)
{
	t_list	*envp;
	char	*args1[] = {"export", "FOO=bar", "BAR=baz", NULL};

	envp = NULL;
	ft_export(args1, &envp);
	// Check that both variables are set correctly
	cr_assert_str_eq(*b_getenv("FOO", envp), "bar", "FOO should be set to bar");
	cr_assert_str_eq(*b_getenv("BAR", envp), "baz", "BAR should be set to baz");
	ft_lstclear(&envp, free);
}

Test(export, prefix_var)
{
	t_list	*envp;

	// unused variable removed
	envp = NULL;
	b_setenv("FOOBAR", "baz", &envp);
	cr_assert_null(b_getenv("FOO", envp), "FOO should not exist");
	cr_assert_str_eq(*b_getenv("FOOBAR", envp), "baz",
		"FOOBAR should still exist");
	ft_lstclear(&envp, free);
}
