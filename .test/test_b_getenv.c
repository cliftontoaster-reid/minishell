/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_b_getenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/01 16:10:59 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

static void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

Test(b_getenv, basic_functionality)
{
	char	*envp[] = {"USER=testuser", "HOME=/home/testuser",
			"SHELL=/bin/bash", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	result = b_getenv("USER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "testuser");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("HOME", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "/home/testuser");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("SHELL", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "/bin/bash");
	cr_assert_null(result[1]);
	free_string_array(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, nonexistent_key)
{
	char	*envp[] = {"USER=testuser", "HOME=/home/testuser", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	result = b_getenv("NONEXISTENT", env_list);
	cr_assert_null(result);
	result = b_getenv("PATH", env_list);
	cr_assert_null(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, null_inputs)
{
	char	*envp[] = {"USER=testuser", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	// Test NULL key - should return all environment variables
	result = b_getenv(NULL, env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "USER=testuser");
	cr_assert_null(result[1]);
	free_string_array(result);
	// Test NULL env_list
	result = b_getenv("USER", NULL);
	cr_assert_null(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, empty_key)
{
	char	*envp[] = {"USER=testuser", "NORMAL=value", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	result = b_getenv("", env_list);
	cr_assert_null(result); // Empty key should not be found
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, empty_value)
{
	char	*envp[] = {"EMPTY_VAR=", "USER=testuser", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	result = b_getenv("EMPTY_VAR", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("USER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "testuser");
	cr_assert_null(result[1]);
	free_string_array(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, case_sensitivity)
{
	char	*envp[] = {"USER=testuser", "user=lowercase", "User=mixedcase",
			NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	result = b_getenv("USER", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "testuser");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("user", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "lowercase");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("User", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "mixedcase");
	cr_assert_null(result[1]);
	free_string_array(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, complex_values)
{
	char	*envp[] = {"URL=http://example.com/path?param=value",
			"PATH=/usr/local/bin:/usr/bin:/bin",
			"SPECIAL=!@#$%^&*()[]{}|\\:;\"'<>,.?/", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	result = b_getenv("URL", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "http://example.com/path?param=value");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("PATH", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "/usr/local/bin:/usr/bin:/bin");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("SPECIAL", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "!@#$%^&*()[]{}|\\:;\"'<>,.?/");
	cr_assert_null(result[1]);
	free_string_array(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, first_match_wins)
{
	t_list	*env_list;
	char	**result;

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
	result = b_getenv("DUPLICATE", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "first_value");
	cr_assert_null(result[1]);
	free_string_array(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, memory_independence)
{
	char	*envp[] = {"TEST=original_value", NULL};
	t_list	*env_list;

	char **result1, **result2;
	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	result1 = b_getenv("TEST", env_list);
	cr_assert_not_null(result1);
	cr_assert_not_null(result1[0]);
	cr_assert_str_eq(result1[0], "original_value");
	cr_assert_null(result1[1]);
	result2 = b_getenv("TEST", env_list);
	cr_assert_not_null(result2);
	cr_assert_not_null(result2[0]);
	cr_assert_str_eq(result2[0], "original_value");
	cr_assert_null(result2[1]);
	// Modify one result, the other should be unaffected
	result1[0][0] = 'X';
	cr_assert_str_eq(result2[0], "original_value");
	cr_assert_str_neq(result1[0], result2[0]);
	free_string_array(result1);
	free_string_array(result2);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, single_character_keys_and_values)
{
	char	*envp[] = {"A=1", "B=2", "X=Y", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	result = b_getenv("A", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "1");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("B", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "2");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("X", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "Y");
	cr_assert_null(result[1]);
	free_string_array(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, partial_key_match)
{
	char	*envp[] = {"HOME=/home/user", "HOSTNAME=mycomputer", NULL};
	t_list	*env_list;
	char	**result;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	// Should not find partial matches
	result = b_getenv("HOM", env_list);
	cr_assert_null(result);
	result = b_getenv("HOST", env_list);
	cr_assert_null(result);
	// Should find exact matches
	result = b_getenv("HOME", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "/home/user");
	cr_assert_null(result[1]);
	free_string_array(result);
	result = b_getenv("HOSTNAME", env_list);
	cr_assert_not_null(result);
	cr_assert_not_null(result[0]);
	cr_assert_str_eq(result[0], "mycomputer");
	cr_assert_null(result[1]);
	free_string_array(result);
	ft_lstclear(&env_list, free_env_data);
}

Test(b_getenv, get_all_env_variables)
{
	char	*envp[] = {"USER=testuser", "HOME=/home/testuser",
			"SHELL=/bin/bash", NULL};
	t_list	*env_list;
	char	**result;
	int		count;
	int		found_user = 0, found_home = 0, found_shell;

	env_list = b_fromenvp(envp);
	cr_assert_not_null(env_list);
	// Test getting all environment variables by passing NULL as key
	result = b_getenv(NULL, env_list);
	cr_assert_not_null(result);
	// Count the number of environment variables returned
	count = 0;
	while (result[count])
		count++;
	// Should return all 3 environment variables
	cr_assert_eq(count, 3);
	// Check that all expected environment variables are present
	found_user = 0, found_home = 0, found_shell = 0;
	for (int i = 0; i < count; i++)
	{
		if (ft_strncmp(result[i], "USER=testuser", 13) == 0)
			found_user = 1;
		else if (ft_strncmp(result[i], "HOME=/home/testuser", 19) == 0)
			found_home = 1;
		else if (ft_strncmp(result[i], "SHELL=/bin/bash", 15) == 0)
			found_shell = 1;
	}
	cr_assert_eq(found_user, 1);
	cr_assert_eq(found_home, 1);
	cr_assert_eq(found_shell, 1);
	free_string_array(result);
	ft_lstclear(&env_list, free_env_data);
}
