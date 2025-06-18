/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:13:11 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/18 13:15:09 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
#include "utils.h"
#include <string.h>

Test(ft_strjoin_free, basic_functionality)
{
	char	*s1;
	char	*s2;
	char	*result;

	s1 = ft_strdup("Hello ");
	s2 = ft_strdup("World");
	cr_assert_not_null(s1);
	cr_assert_not_null(s2);
	result = ft_strjoin_free(s1, s2);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "Hello World");
	free(result);
}

Test(ft_strjoin_free, empty_strings)
{
	char	*s1;
	char	*s2;
	char	*result;

	// Test empty first string
	s1 = ft_strdup("");
	s2 = ft_strdup("World");
	cr_assert_not_null(s1);
	cr_assert_not_null(s2);
	result = ft_strjoin_free(s1, s2);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "World");
	free(result);
	// Test empty second string
	s1 = ft_strdup("Hello");
	s2 = ft_strdup("");
	cr_assert_not_null(s1);
	cr_assert_not_null(s2);
	result = ft_strjoin_free(s1, s2);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "Hello");
	free(result);
	// Test both empty strings
	s1 = ft_strdup("");
	s2 = ft_strdup("");
	cr_assert_not_null(s1);
	cr_assert_not_null(s2);
	result = ft_strjoin_free(s1, s2);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "");
	free(result);
}

Test(ft_strjoin_free, null_inputs)
{
	char	*s1;
	char	*s2;
	char	*result;

	// Test first string NULL
	s1 = NULL;
	s2 = ft_strdup("World");
	cr_assert_not_null(s2);
	result = ft_strjoin_free(s1, s2);
	cr_assert_eq(result, s2);
	cr_assert_str_eq(result, "World");
	free(result);
	// Test second string NULL
	s1 = ft_strdup("Hello");
	s2 = NULL;
	cr_assert_not_null(s1);
	result = ft_strjoin_free(s1, s2);
	cr_assert_eq(result, s1);
	cr_assert_str_eq(result, "Hello");
	free(result);
	// Test both strings NULL
	s1 = NULL;
	s2 = NULL;
	result = ft_strjoin_free(s1, s2);
	cr_assert_null(result);
}

Test(ft_strjoin_free, long_strings)
{
	char	*s1;
	char	*s2;
	char	*result;
	char	*expected;

	s1 = ft_strdup("This is a very long string that should test the allocation and copying mechanisms of the function. ");
	s2 = ft_strdup("This is another very long string to ensure that the function handles large inputs correctly and efficiently.");
	cr_assert_not_null(s1);
	cr_assert_not_null(s2);
	expected = "This is a very long string that should test the allocation and copying mechanisms of the function. This is another very long string to ensure that the function handles large inputs correctly and efficiently.";
	result = ft_strjoin_free(s1, s2);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, expected);
	cr_assert_eq(strlen(result), strlen(expected));
	free(result);
}

Test(ft_strjoin_free, special_characters)
{
	char	*s1;
	char	*s2;
	char	*result;

	s1 = ft_strdup("Hello\n");
	s2 = ft_strdup("\tWorld!\0");
	cr_assert_not_null(s1);
	cr_assert_not_null(s2);
	result = ft_strjoin_free(s1, s2);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "Hello\n\tWorld!");
	free(result);
}

Test(ft_strjoin_free, single_characters)
{
	char	*s1;
	char	*s2;
	char	*result;

	s1 = ft_strdup("A");
	s2 = ft_strdup("B");
	cr_assert_not_null(s1);
	cr_assert_not_null(s2);
	result = ft_strjoin_free(s1, s2);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "AB");
	cr_assert_eq(strlen(result), 2);
	free(result);
}

Test(ft_strjoin_free, memory_cleanup)
{
	char	*s1;
	char	*s2;
	char	*result;
	char	*original_s1;
	char	*original_s2;

	// Create strings and keep references to test memory cleanup
	s1 = ft_strdup("Test ");
	s2 = ft_strdup("Memory");
	cr_assert_not_null(s1);
	cr_assert_not_null(s2);
	// Store original pointers to verify they get freed
	original_s1 = s1;
	original_s2 = s2;
	result = ft_strjoin_free(s1, s2);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "Test Memory");
	// The original pointers should have been freed by ft_strjoin_free
	// We can't directly test this, but we verify the result is correct
	cr_assert_neq(result, original_s1);
	cr_assert_neq(result, original_s2);
	free(result);
}

Test(ft_strjoin_free, repeated_operations)
{
	char	*result;
	char	*temp;

	// Test chaining multiple ft_strjoin_free operations
	result = ft_strdup("Start");
	cr_assert_not_null(result);
	temp = ft_strdup(" -> ");
	result = ft_strjoin_free(result, temp);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "Start -> ");
	temp = ft_strdup("Middle");
	result = ft_strjoin_free(result, temp);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "Start -> Middle");
	temp = ft_strdup(" -> End");
	result = ft_strjoin_free(result, temp);
	cr_assert_not_null(result);
	cr_assert_str_eq(result, "Start -> Middle -> End");
	free(result);
}
