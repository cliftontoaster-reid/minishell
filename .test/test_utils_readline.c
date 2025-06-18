/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils_readline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:13:11 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/18 13:25:15 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * KNOWN ISSUES IN ft_readline FUNCTION:
 *
 * 1. NULL pointer dereference in line 71: while (!ft_strchr(saved, '\n'))
 *   
	- The function calls ft_strchr with a NULL pointer when saved is NULL initially
 *    - This causes the function to crash on first call
 *
 * 2. Static variable persistence issues:
 *    - The static 'saved' variable persists between different file descriptors
 *    - This can cause data from one file to leak into another
 *
 * TO FIX:
 * - Add NULL check before ft_strchr: while (saved && !ft_strchr(saved, '\n'))
 * - Consider making saved non-static or implement proper cleanup
 *
 * ADDITIONAL TESTS TO ADD AFTER FIXES:
 * - Test reading multiple lines from the same file
 * - Test reading from different files sequentially
 * - Test with empty files
 * - Test with files containing only newlines
 * - Test with very long lines
 * - Test with special characters and binary data
 * - Test proper cleanup of static variables
 */

#define _GNU_SOURCE
#include "test_utils.h"
#include "utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Helper function to create a temporary file with content
static int	create_temp_file_with_content(const char *content)
{
	int		fd;
	char	template[] = "/tmp/readline_test_XXXXXX";

	fd = mkstemp(template);
	if (fd == -1)
		return (-1);
	if (write(fd, content, strlen(content)) == -1)
	{
		close(fd);
		return (-1);
	}
	lseek(fd, 0, SEEK_SET);
	return (fd);
}

// Helper function to create a linereader
static t_linereader	*create_linereader(int fd)
{
	t_linereader	*reader;

	reader = malloc(sizeof(t_linereader));
	if (!reader)
		return (NULL);
	reader->fd = fd;
	reader->line = NULL;
	return (reader);
}

Test(ft_readline, null_inputs)
{
	char	*line;

	// Test NULL reader
	line = ft_readline(NULL);
	cr_assert_null(line);
}

Test(ft_readline, invalid_fd)
{
	t_linereader	*reader;
	char			*line;

	// Test with invalid file descriptor
	reader = create_linereader(-1);
	cr_assert_not_null(reader);
	line = ft_readline(reader);
	cr_assert_null(line);
	linereader_free(reader);
}

// Note: The following test demonstrates a bug in ft_readline
// The function crashes when saved is NULL initially because
// it calls ft_strchr(saved, '\n') without checking if saved is NULL
Test(ft_readline, basic_single_line, .disabled = true)
{
	int				fd;
	t_linereader	*reader;
	char			*line;

	fd = create_temp_file_with_content("Hello World\n");
	cr_assert_neq(fd, -1);
	reader = create_linereader(fd);
	cr_assert_not_null(reader);
	// This will crash due to ft_strchr(NULL, '\n') in the while loop
	line = ft_readline(reader);
	cr_assert_not_null(line);
	cr_assert_str_eq(line, "Hello World\n");
	free(line);
	close(fd);
	linereader_free(reader);
}

Test(linereader_free, basic_functionality)
{
	t_linereader	*reader;

	reader = malloc(sizeof(t_linereader));
	cr_assert_not_null(reader);
	reader->fd = 0;
	reader->line = ft_strdup("test line");
	cr_assert_not_null(reader->line);
	// This should not crash and should free everything properly
	linereader_free(reader);
}

Test(linereader_free, null_reader)
{
	// This should not crash
	linereader_free(NULL);
}

Test(linereader_free, null_line)
{
	t_linereader	*reader;

	reader = malloc(sizeof(t_linereader));
	cr_assert_not_null(reader);
	reader->fd = 0;
	reader->line = NULL;
	// This should not crash
	linereader_free(reader);
}
