/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 13:39:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GIT_H
# define GIT_H

# include <stdbool.h>
# include <sys/types.h>

/**

	* @brief Find the .git directory by traversing up from
  * current working directory
 * @return Pointer to the path of the .git directory, or NULL if not found
 *
 * This function searches for a .git directory by starting from the current
 * working directory and traversing up the directory tree until it finds one
 * or reaches the root directory. The caller is responsible for freeing the
 * returned path.
 */
char	*find_git_dir(void);

/**
 * @brief Check if current directory is inside a git repository
 * @return true if current directory is in a git repository, false otherwise
 *
 * This function uses find_git_dir() to determine if the current working
 * directory is part of a git repository.
 */
bool	is_repo(void);

/**
 * @brief Read current branch name from .git/HEAD
 * @return Pointer to the current branch name, or NULL if not in a git repo
 *
 * This function reads the .git/HEAD file to determine the current branch.
 * It handles both direct branch references and symbolic references.
 * The caller is responsible for freeing the returned string.
 */
char	*git_getbranch(void);

/**
 * @brief Check if there are uncommitted changes in the working directory
 * @return true if there are uncommitted changes, false otherwise
 *
 * This function executes 'git diff --quiet --exit-code' to check for
 * uncommitted changes in the working directory.
 */
bool	is_git_changes(void);

/**
 * @brief Check if there are staged changes ready to commit
 * @return true if there are staged changes, false otherwise
 *
 * This function executes 'git diff --staged --quiet --exit-code' to check
 * for staged changes in the index.
 */
bool	is_git_changes_staged(void);

/**
 * @brief Print git status information for the shell prompt
 *
 * This function displays git information including the current branch name
 * and indicators for uncommitted and staged changes. It uses ANSI color
 * codes to format the output.
 */
void	git_message(void);

/**
 * @brief Extract branch name from git HEAD file content
 * @param buffer Buffer containing the content of .git/HEAD file
 * @param n Length of the buffer content
 * @return Pointer to the extracted branch name, or NULL on failure
 *
 * This function parses the content of .git/HEAD to extract the branch name.
 * It handles both symbolic references (ref: refs/heads/branch) and direct
 * commit hashes. The caller is responsible for freeing the returned string.
 */
char	*get_branch_name(char *buffer, ssize_t n);

/**
 * @brief Read and return the content of .git/HEAD file
 * @param fd File descriptor of the opened .git/HEAD file
 * @return Pointer to the file content, or NULL on failure
 *
 * This function reads the entire content of the .git/HEAD file and
 * returns it as a null-terminated string. The file descriptor is
 * closed after reading. The caller is responsible for freeing the
 * returned string.
 */
char	*read_head_file(int fd);

/**
 * @brief Open .git/HEAD file and return file descriptor as string
 * @param git_dir Path to the .git directory (will be freed)
 * @return String representation of the file descriptor, or NULL on failure
 *
 * This function constructs the path to .git/HEAD, opens it, and returns
 * the file descriptor converted to a string. The git_dir parameter is
 * freed after use. The caller is responsible for freeing the returned string.
 */
char	*open_head_file(char *git_dir);

#endif
