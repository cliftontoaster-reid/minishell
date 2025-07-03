/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:00:00 by creid             #+#    #+#             */
/*   Updated: 2025/07/03 15:53:25 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "test_utils.h"
#include <criterion/redirect.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH_MAX 4096

// Forward declaration for ft_cd if it's not in a header included by test_utils.h
void		ft_cd(char **argv, t_list **envp);

static void	setup(void)
{
	// Create a temporary directory for testing
	mkdir("tmp_test_dir", 0755);
}

static void	teardown(void)
{
	// Clean up the temporary directory
	rmdir("tmp_test_dir");
}

Test(cd, change_to_existing_dir, .init = setup, .fini = teardown)
{
	t_list		*envp;
	char		*argv[] = {"cd", "tmp_test_dir", NULL};
	char		cwd_before[PATH_MAX];
	char		cwd_after[PATH_MAX];
	char		**pwd_val;
	size_t		len;
	const char	*suffix = "/tmp_test_dir";
	size_t		suffix_len;

	envp = NULL;
	b_setenv("PWD", getcwd(cwd_before, sizeof(cwd_before)), &envp);
	ft_cd(argv, &envp);
	getcwd(cwd_after, sizeof(cwd_after));
	cr_assert_str_neq(cwd_before, cwd_after,
		"The directory should have changed.");
	// Check if cwd_after ends with "/tmp_test_dir"
	len = strlen(cwd_after);
	suffix_len = strlen(suffix);
	cr_assert(len >= suffix_len && strcmp(cwd_after + len - suffix_len,
			suffix) == 0, "The new directory should be tmp_test_dir.");
	pwd_val = b_getenv("PWD", envp);
	cr_assert_str_eq(*pwd_val, cwd_after,
		"The PWD environment variable was not updated correctly.");
	// Go back to original directory to allow teardown to succeed
	chdir(cwd_before);
	free(*pwd_val);
	free(pwd_val);
	ft_lstclear(&envp, free);
}

Test(cd, no_such_file_or_directory, .init = cr_redirect_stdout)
{
	t_list	*envp;
	char	*argv[] = {"cd", "non_existent_dir", NULL};
	char	cwd_before[PATH_MAX];
	char	cwd_after[PATH_MAX];

	envp = NULL;
	getcwd(cwd_before, sizeof(cwd_before));
	b_setenv("PWD", cwd_before, &envp);
	ft_cd(argv, &envp);
	getcwd(cwd_after, sizeof(cwd_after));
	cr_assert_str_eq(cwd_before, cwd_after,
		"The directory should not have changed.");
	fflush(stdout);
	cr_assert_stdout_eq_str("cd: no such file or directory: non_existent_dir\n");
	ft_lstclear(&envp, free);
}

Test(cd, no_argument, .init = cr_redirect_stderr)
{
	t_list	*envp;
	char	*argv[] = {"cd", NULL};

	envp = NULL;
	ft_cd(argv, &envp);
	fflush(stderr);
	cr_assert_stderr_eq_str("cd: no such file or directory: ");
	ft_lstclear(&envp, free);
}
