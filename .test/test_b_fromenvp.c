/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_b_fromenvp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:33:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

Test(b_fromenvp, basic_test)
{
	char	*envp[] = {"USER=test", "HOME=/home/test", "PATH=/usr/bin:/bin",
			NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 3);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, empty_envp)
{
	char	*envp[] = {NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_null(env_list);
}

Test(b_fromenvp, single_variable)
{
	char	*envp[] = {"TEST=value", NULL};
	t_list	*env_list;
	t_env	*env_data;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 1);
	env_data = (t_env *)env_list->content;
	cr_assert_str_eq(env_data->key, "TEST");
	cr_assert_str_eq(env_data->value, "value");
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, empty_value)
{
	char	*envp[] = {"EMPTY_VAR=", NULL};
	t_list	*env_list;
	t_env	*env_data;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 1);
	env_data = (t_env *)env_list->content;
	cr_assert_str_eq(env_data->key, "EMPTY_VAR");
	cr_assert_str_eq(env_data->value, "");
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, value_with_equals)
{
	char	*envp[] = {"COMPLEX=value=with=equals", NULL};
	t_list	*env_list;
	t_env	*env_data;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 1);
	env_data = (t_env *)env_list->content;
	cr_assert_str_eq(env_data->key, "COMPLEX");
	cr_assert_str_eq(env_data->value, "value=with=equals");
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, multiple_variables_order)
{
	char	*envp[] = {"FIRST=1", "SECOND=2", "THIRD=3", NULL};
	t_list	*env_list;
	t_env	*env_data;
	t_list	*current;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 3);
	// Check first variable
	current = env_list;
	env_data = (t_env *)current->content;
	cr_assert_str_eq(env_data->key, "FIRST");
	cr_assert_str_eq(env_data->value, "1");
	// Check second variable
	current = current->next;
	env_data = (t_env *)current->content;
	cr_assert_str_eq(env_data->key, "SECOND");
	cr_assert_str_eq(env_data->value, "2");
	// Check third variable
	current = current->next;
	env_data = (t_env *)current->content;
	cr_assert_str_eq(env_data->key, "THIRD");
	cr_assert_str_eq(env_data->value, "3");
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, invalid_no_equals)
{
	char	*envp[] = {"INVALID_VAR", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_null(env_list);
}

Test(b_fromenvp, invalid_no_key)
{
	char	*envp[] = {"=value", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	cr_assert_null(env_list);
}

Test(b_fromenvp, mixed_valid_invalid)
{
	char	*envp[] = {"VALID=value", "INVALID", NULL};
	t_list	*env_list;

	env_list = b_fromenvp(envp);
	// Should return NULL because one entry is invalid
	cr_assert_null(env_list);
}

Test(b_fromenvp, special_characters_in_value)
{
	char	*envp[] = {"SPECIAL=!@#$%^&*()[]{}|\\:;\"'<>,.?/", NULL};
	t_list	*env_list;
	t_env	*env_data;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 1);
	env_data = (t_env *)env_list->content;
	cr_assert_str_eq(env_data->key, "SPECIAL");
	cr_assert_str_eq(env_data->value, "!@#$%^&*()[]{}|\\:;\"'<>,.?/");
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, long_values)
{
	char	*long_value;
	char	*envp[] = {"LONG_VAR=very_long_value_that_contains_multiple_words_and_special_characters_123456789",
			NULL};
	t_list	*env_list;
	t_env	*env_data;

	long_value = "very_long_value_that_contains_multiple_words_and_special_characters_123456789";
	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 1);
	env_data = (t_env *)env_list->content;
	cr_assert_str_eq(env_data->key, "LONG_VAR");
	cr_assert_str_eq(env_data->value, long_value);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, numeric_key)
{
	char	*envp[] = {"123=numeric_key", NULL};
	t_list	*env_list;
	t_env	*env_data;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 1);
	env_data = (t_env *)env_list->content;
	cr_assert_str_eq(env_data->key, "123");
	cr_assert_str_eq(env_data->value, "numeric_key");
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, realistic_environment)
{
	char	*envp[] = {"USER=testuser", "HOME=/home/testuser",
			"PATH=/usr/local/bin:/usr/bin:/bin", "SHELL=/bin/bash",
			"PWD=/home/testuser/project", "LANG=en_US.UTF-8",
			"TERM=xterm-256color", NULL};
	t_list	*env_list;
	t_env	*env_data;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 7);
	// Test specific variables using helper function
	env_data = find_env_var(env_list, "USER");
	cr_assert_not_null(env_data);
	cr_assert_str_eq(env_data->value, "testuser");
	env_data = find_env_var(env_list, "HOME");
	cr_assert_not_null(env_data);
	cr_assert_str_eq(env_data->value, "/home/testuser");
	env_data = find_env_var(env_list, "PATH");
	cr_assert_not_null(env_data);
	cr_assert_str_eq(env_data->value, "/usr/local/bin:/usr/bin:/bin");
	// Test non-existent variable
	env_data = find_env_var(env_list, "NONEXISTENT");
	cr_assert_null(env_data);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, underscore_and_mixed_case)
{
	char	*envp[] = {"_UNDERSCORE=value1", "MixedCase=value2",
			"UPPER_CASE=value3", "lower_case=value4", NULL};
	t_list	*env_list;
	t_env	*env_data;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 4);
	env_data = find_env_var(env_list, "_UNDERSCORE");
	cr_assert_not_null(env_data);
	cr_assert_str_eq(env_data->value, "value1");
	env_data = find_env_var(env_list, "MixedCase");
	cr_assert_not_null(env_data);
	cr_assert_str_eq(env_data->value, "value2");
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, multiple_equals_signs_in_value)
{
	char	*envp[] = {"URL=http://example.com/path?param=value", NULL};
	t_list	*env_list;
	t_env	*env_data;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 1);
	env_data = (t_env *)env_list->content;
	cr_assert_str_eq(env_data->key, "URL");
	cr_assert_str_eq(env_data->value, "http://example.com/path?param=value");
	ft_lstclear(&env_list, free_env_data);
}

Test(b_fromenvp, complex_values_with_equals)
{
	char	*envp[] = {"DATABASE_URL=postgres://user:pass@host:5432/db?sslmode=require",
			"QUERY_STRING=name=john&age=30&city=new=york", "MATH_EXPR=2+2=4",
			NULL};
	t_list	*env_list;
	t_env	*env_data;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 3);
	env_data = find_env_var(env_list, "DATABASE_URL");
	cr_assert_not_null(env_data);
	cr_assert_str_eq(env_data->value,
		"postgres://user:pass@host:5432/db?sslmode=require");
	env_data = find_env_var(env_list, "QUERY_STRING");
	cr_assert_not_null(env_data);
	cr_assert_str_eq(env_data->value, "name=john&age=30&city=new=york");
	env_data = find_env_var(env_list, "MATH_EXPR");
	cr_assert_not_null(env_data);
	cr_assert_str_eq(env_data->value, "2+2=4");
	ft_lstclear(&env_list, free_env_data);
}
