/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creid <creid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:10:00 by creid             #+#    #+#             */
/*   Updated: 2025/07/03 17:10:00 by creid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Forward declaration for ft_exit if not in a header
void		ft_exit(char **s, t_reader *reader);

static int	run_exit_and_get_code(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	cr_assert_neq(pid, -1, "fork failed");
	if (pid == 0)
	{
		// Redirect stdout and stderr to /dev/null
		freopen("/dev/null", "w", stdout);
		freopen("/dev/null", "w", stderr);
		ft_exit(args, NULL);
		_exit(42); // Should never reach here
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

Test(exit, no_argument)
{
	char	*args[] = {"exit", NULL};
	int		code;

	code = run_exit_and_get_code(args);
	cr_assert_eq(code, 0, "exit with no argument should return (0");
}

Test(exit, numeric_argument)
{
	char	*args[] = {"exit", "42", NULL};
	int		code;

	code = run_exit_and_get_code(args);
	cr_assert_eq(code, 42, "exit with argument 42 should return (42");
}

Test(exit, argument_out_of_range)
{
	char	*args[] = {"exit", "300", NULL};
	int		code;

	code = run_exit_and_get_code(args);
	cr_assert_eq(code, 44, "exit with argument 300 should return (44)");
}

Test(exit, negative_argument)
{
	char	*args[] = {"exit", "-1", NULL};
	int		code;

	code = run_exit_and_get_code(args);
	cr_assert_eq(code, 255, "exit with argument <0 should return (255");
}

Test(exit, non_numeric_argument)
{
	pid_t	pid;
	char	*args[] = {"exit", "notanumber", NULL};
	int		status;

	pid = fork();
	cr_assert_neq(pid, -1, "fork failed");
	if (pid == 0)
	{
		freopen("/dev/null", "w", stdout);
		freopen("/dev/null", "w", stderr);
		ft_exit(args, NULL);
		_exit(42);
	}
	waitpid(pid, &status, 0);
	// Should not exit, but print error and return
}

Test(exit, too_many_arguments)
{
	pid_t	pid;
	char	*args[] = {"exit", "1", "2", NULL};
	int		status;

	pid = fork();
	cr_assert_neq(pid, -1, "fork failed");
	if (pid == 0)
	{
		freopen("/dev/null", "w", stdout);
		freopen("/dev/null", "w", stderr);
		ft_exit(args, NULL);
		_exit(42);
	}
	waitpid(pid, &status, 0);
	// Should not exit, but print error and return
}
