/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_b_varexists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:33:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

Test(b_varexists, basic_functionality)
{
	char	*envp[] = {"USER=testuser", "HOME=/home/testuser",
			"SHELL=/bin/bash", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("USER", env_list), true);
	cr_assert_eq(b_varexists("HOME", env_list), true);
	cr_assert_eq(b_varexists("SHELL", env_list), true);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, nonexistent_variable)
{
	char	*envp[] = {"USER=testuser", "HOME=/home/testuser", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("NONEXISTENT", env_list), false);
	cr_assert_eq(b_varexists("PATH", env_list), false);
	cr_assert_eq(b_varexists("SHELL", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, null_inputs)
{
	char	*envp[] = {"USER=testuser", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	// Test NULL key
	cr_assert_eq(b_varexists(NULL, env_list), false);
	// Test NULL env_list
	cr_assert_eq(b_varexists("USER", NULL), false);
	// Test both NULL
	cr_assert_eq(b_varexists(NULL, NULL), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, empty_key)
{
	char	*envp[] = {"USER=testuser", "NORMAL=value", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, empty_value_variable)
{
	char	*envp[] = {"EMPTY_VAR=", "USER=testuser", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("EMPTY_VAR", env_list), true);
	cr_assert_eq(b_varexists("USER", env_list), true);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, case_sensitivity)
{
	char	*envp[] = {"USER=testuser", "user=lowercase", "User=mixedcase",
			NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("USER", env_list), true);
	cr_assert_eq(b_varexists("user", env_list), true);
	cr_assert_eq(b_varexists("User", env_list), true);
	cr_assert_eq(b_varexists("uSER", env_list), false);
	cr_assert_eq(b_varexists("UsEr", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, single_character_keys)
{
	char	*envp[] = {"A=1", "B=2", "X=Y", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("A", env_list), true);
	cr_assert_eq(b_varexists("B", env_list), true);
	cr_assert_eq(b_varexists("X", env_list), true);
	cr_assert_eq(b_varexists("C", env_list), false);
	cr_assert_eq(b_varexists("Z", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, partial_key_match)
{
	char	*envp[] = {"USERNAME=testuser", "USER=test", "USE=val", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("USER", env_list), true);
	cr_assert_eq(b_varexists("USE", env_list), true);
	cr_assert_eq(b_varexists("USERNAME", env_list), true);
	cr_assert_eq(b_varexists("USERN", env_list), false);
	cr_assert_eq(b_varexists("U", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, numeric_and_special_keys)
{
	char	*envp[] = {"123=numeric", "_UNDERSCORE=value", "DASH-VAR=test",
			NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("123", env_list), true);
	cr_assert_eq(b_varexists("_UNDERSCORE", env_list), true);
	cr_assert_eq(b_varexists("DASH-VAR", env_list), true);
	cr_assert_eq(b_varexists("456", env_list), false);
	cr_assert_eq(b_varexists("UNDERSCORE", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, empty_environment)
{
	char	*envp[] = {NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_null(env_list);
	cr_assert_eq(b_varexists("USER", env_list), false);
	cr_assert_eq(b_varexists("HOME", env_list), false);
	cr_assert_eq(b_varexists("", env_list), false);
}

Test(b_varexists, first_and_last_variables)
{
	char	*envp[] = {"FIRST=1", "MIDDLE=2", "LAST=3", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("FIRST", env_list), true);
	cr_assert_eq(b_varexists("MIDDLE", env_list), true);
	cr_assert_eq(b_varexists("LAST", env_list), true);
	cr_assert_eq(b_varexists("ZERO", env_list), false);
	cr_assert_eq(b_varexists("FINAL", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, complex_variable_names)
{
	char	*envp[] = {"PATH_TO_HOME=/home/user",
			"HTTP_PROXY=proxy.example.com", "DATABASE_URL=postgres://localhost",
			NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(b_varexists("PATH_TO_HOME", env_list), true);
	cr_assert_eq(b_varexists("HTTP_PROXY", env_list), true);
	cr_assert_eq(b_varexists("DATABASE_URL", env_list), true);
	cr_assert_eq(b_varexists("PATH", env_list), false);
	cr_assert_eq(b_varexists("PROXY", env_list), false);
	cr_assert_eq(b_varexists("URL", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, duplicate_keys_first_match)
{
	t_list	*env_list;

	// Manually create environment with duplicate keys
	env_list = NULL;
	t_env *env1, *env2;
	env1 = malloc(sizeof(t_env));
	cr_assert_not_null(env1);
	env1->key = ft_strdup("DUPLICATE");
	env1->value = ft_strdup("first_value");
	ft_lstadd_back(&env_list, ft_lstnew(env1));
	env2 = malloc(sizeof(t_env));
	cr_assert_not_null(env2);
	env2->key = ft_strdup("DUPLICATE");
	env2->value = ft_strdup("second_value");
	ft_lstadd_back(&env_list, ft_lstnew(env2));
	cr_assert_eq(b_varexists("DUPLICATE", env_list), true);
	cr_assert_eq(b_varexists("NONEXISTENT", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_varexists, realistic_environment)
{
	char	*envp[] = {"USER=testuser", "HOME=/home/testuser",
			"TERM=xterm-256color", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	// Test variables that should exist
	cr_assert_eq(b_varexists("USER", env_list), true);
	cr_assert_eq(b_varexists("HOME", env_list), true);
	cr_assert_eq(b_varexists("TERM", env_list), true);
	// Test variables that should not exist
	cr_assert_eq(b_varexists("NONEXISTENT", env_list), false);
	cr_assert_eq(b_varexists("RANDOM_VAR", env_list), false);
	cr_assert_eq(b_varexists("FAKE", env_list), false);
	cr_assert_eq(b_varexists("PATH", env_list), false);
	ft_lstclear(&env_list, free_env_data);
}
