/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_b_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/01 16:17:39 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

Test(b_setenv, set_new_variable)
{
	char	*envp[] = {"USER=testuser", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 1);
	b_setenv("HOME", "/home/testuser", &env_list);
	cr_assert_eq(ft_lstsize(env_list), 2);
	result = b_getenv("HOME", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "/home/testuser");
	free(result[0]);
	free(result);
	result = b_getenv("USER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "testuser");
	free(result[0]);
	free(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, update_existing_variable)
{
	char	*envp[] = {"USER=olduser", "HOME=/old/home", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 2);
	b_setenv("USER", "newuser", &env_list);
	cr_assert_eq(ft_lstsize(env_list), 2); // Should not add a new entry
	result = b_getenv("USER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "newuser");
	free(result[0]);
	free(result);
	result = b_getenv("HOME", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "/old/home");
	free(result[0]);
	free(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, set_empty_value)
{
	char	*envp[] = {"USER=testuser", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	b_setenv("EMPTY_VAR", "", &env_list);
	cr_assert_eq(ft_lstsize(env_list), 2);
	result = b_getenv("EMPTY_VAR", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "");
	free(result[0]);
	free(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, null_inputs)
{
	char	*envp[] = {"USER=testuser", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	cr_assert_eq(ft_lstsize(env_list), 1);
	// Test NULL key
	b_setenv(NULL, "value", &env_list);
	cr_assert_eq(ft_lstsize(env_list), 1); // Should not change
	// Test NULL value
	b_setenv("TEST", NULL, &env_list);
	cr_assert_eq(ft_lstsize(env_list), 1); // Should not change
	// Test NULL envp (should not crash)
	b_setenv("TEST", "value", NULL);
	// Verify original data is unchanged
	result = b_getenv("USER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "testuser");
	free(result[0]);
	free(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, case_sensitivity)
{
	char	*envp[] = {"USER=testuser", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	b_setenv("user", "lowercase", &env_list);
	b_setenv("User", "mixedcase", &env_list);
	cr_assert_eq(ft_lstsize(env_list), 3); // USER, user, User
	result = b_getenv("USER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "testuser");
	free(result[0]);
	free(result);
	result = b_getenv("user", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "lowercase");
	free(result[0]);
	free(result);
	result = b_getenv("User", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "mixedcase");
	free(result[0]);
	free(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, complex_values)
{
	char	*envp[] = {"USER=testuser", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	b_setenv("URL", "http://example.com/path?param=value", &env_list);
	b_setenv("PATH", "/usr/local/bin:/usr/bin:/bin", &env_list);
	b_setenv("SPECIAL", "!@#$%^&*()[]{}|\\:;\"'<>,.?/", &env_list);
	result = b_getenv("URL", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "http://example.com/path?param=value");
	free(result[0]);
	free(result);
	result = b_getenv("PATH", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "/usr/local/bin:/usr/bin:/bin");
	free(result[0]);
	free(result);
	result = b_getenv("SPECIAL", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "!@#$%^&*()[]{}|\\:;\"'<>,.?/");
	free(result[0]);
	free(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, update_to_empty_value)
{
	char	*envp[] = {"TEST=original_value", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	result = b_getenv("TEST", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "original_value");
	free(result[0]);
	free(result);
	b_setenv("TEST", "", &env_list);
	cr_assert_eq(ft_lstsize(env_list), 1); // Should not add new entry
	result = b_getenv("TEST", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "");
	free(result[0]);
	free(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, multiple_updates)
{
	char	*envp[] = {"COUNTER=0", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	b_setenv("COUNTER", "1", &env_list);
	result = b_getenv("COUNTER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "1");
	free(result[0]);
	free(result);
	b_setenv("COUNTER", "2", &env_list);
	result = b_getenv("COUNTER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "2");
	free(result[0]);
	free(result);
	b_setenv("COUNTER", "final", &env_list);
	result = b_getenv("COUNTER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "final");
	free(result[0]);
	free(result);
	cr_assert_eq(ft_lstsize(env_list), 1); // Should still be only one entry
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, single_character_key_and_value)
{
	char	*envp[] = {"A=1", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	b_setenv("B", "2", &env_list);
	b_setenv("A", "X", &env_list); // Update existing
	result = b_getenv("A", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "X");
	free(result[0]);
	free(result);
	result = b_getenv("B", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "2");
	free(result[0]);
	free(result);
	cr_assert_eq(ft_lstsize(env_list), 2);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, empty_list_behavior)
{
	t_list	*env_list;
	char	**result;
	char	*envp[] = {"INITIAL=value", NULL};

	env_list = NULL;
	// Should not crash with empty list
	b_setenv("TEST", "value", &env_list);
	// Create a list with one item first
	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	b_setenv("NEW_VAR", "new_value", &env_list);
	cr_assert_eq(ft_lstsize(env_list), 2);
	result = b_getenv("NEW_VAR", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "new_value");
	free(result[0]);
	free(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_setenv, preserve_order)
{
	char	*envp[] = {"FIRST=1", "SECOND=2", NULL};
	t_list	*env_list;
	t_env	*env_data;
	t_list	*current;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	b_setenv("THIRD", "3", &env_list);
	cr_assert_eq(ft_lstsize(env_list), 3);
	// Check that order is preserved and new item is at the end
	current = env_list;
	env_data = (t_env *)current->content;
	cr_assert_str_eq(env_data->key, "FIRST");
	current = current->next;
	env_data = (t_env *)current->content;
	cr_assert_str_eq(env_data->key, "SECOND");
	current = current->next;
	env_data = (t_env *)current->content;
	cr_assert_str_eq(env_data->key, "THIRD");
	ft_lstclear(&env_list, free_env_data);
}
