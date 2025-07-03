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
	char *output = cr_get_redirected_stdout();
	char *expected[] = {"PWD=/home/test", "USER=test", "HOME=/home/test"};
	size_t expected_size = sizeof(expected) / sizeof(expected[0]);
	qsort(expected, expected_size, sizeof(char *), strcmp);
	char **lines = split_lines(output);
	size_t lines_count = count_lines(lines);
	qsort(lines, lines_count, sizeof(char *), strcmp);
	cr_assert_eq(lines_count, expected_size, "Number of lines in output does not match expected");
	for (size_t i = 0; i < expected_size; i++) {
	    cr_assert_str_eq(lines[i], expected[i], "Line %zu does not match expected", i);
	}
	free_lines(lines);
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
