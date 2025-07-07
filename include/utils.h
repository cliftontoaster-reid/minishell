/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:31:30 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/07 11:40:44 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.h
 * @brief Utility functions and data structures for the minishell project
 * @author jfranc, lfiorell
 * @date 2025-06-12
 */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <stdbool.h>

/**
 * @struct s_iteration
 * @brief Structure to hold iteration counters
 *
 * This structure is commonly used in loops that require multiple
 * iteration variables to keep track of different indices.
 */
typedef struct s_iteration
{
	// First iteration counter
	int				i;
	// Second iteration counter
	int				j;
	// Third iteration counter
	int				k;
}					t_iteration;

/**
 * @struct s_linereader
 * @brief Structure for reading lines from a file descriptor
 *
 * This structure encapsulates the state needed for line-by-line
 * reading from a file descriptor, maintaining the current line
 * buffer and file descriptor.
 */
typedef struct s_linereader
{
	// Current line buffer
	char			*line;
	// File descriptor to read from
	int				fd;
}					t_linereader;

/**
 * @brief Joins two strings and frees the first one
 * @param s1 First string (will be freed after joining)
 * @param s2 Second string to append
 * @return Pointer to the newly allocated joined string, or NULL on failure
 *
 * This function concatenates s1 and s2 into a new string, then frees s1.
 * This is useful for building strings incrementally without memory leaks.
 */
char				*ft_strjoin_free(char *s1, char *s2);

/**
 * @brief Reads a line from a file descriptor using a linereader structure
 * @param reader Pointer to the linereader structure
 * @return Pointer to the read line, or NULL on failure or EOF
 *
 * This function reads a complete line from the file descriptor stored
 * in the reader structure. The line is stored in the reader's line buffer.
 */
char				*ft_readline(t_linereader *reader);

/**
 * @brief Frees memory allocated for a linereader structure
 * @param reader Pointer to the linereader structure to free
 *
 * This function properly deallocates all memory associated with the
 * linereader structure, including the line buffer.
 */
void				linereader_free(t_linereader *reader);

/**
 * @brief Opens a random file descriptor
 * @return File descriptor for random number generation, or -1 on failure
 *
 * This function opens a file descriptor that can be used for generating
 * random numbers, typically from /dev/random or similar source.
 */
int					ft_openrand(void);

/**
 * @brief Opens an unreliable random file descriptor
 * @return File descriptor for unreliable random number generation, or
	-1 on failure
 *
 * This function opens a file descriptor for faster but potentially less
 * secure random number generation, typically from /dev/urandom.
 */
int					ft_openurand(void);

/**
 * @brief Reads an integer from a file descriptor
 * @param fd File descriptor to read from
 * @return The integer value read from the file descriptor
 *
 * This function reads binary data from the file descriptor and
 * interprets it as an integer value.
 */
int					ft_readint(int fd);

/**
 * @brief Reads a long integer from a file descriptor
 * @param fd File descriptor to read from
 * @return The long integer value read from the file descriptor
 *
 * This function reads binary data from the file descriptor and
 * interprets it as a long integer value.
 */
long				ft_readlong(int fd);

/**
 * @brief Reads a long long integer from a file descriptor
 * @param fd File descriptor to read from
 * @return The long long integer value read from the file descriptor
 *
 * This function reads binary data from the file descriptor and
 * interprets it as a long long integer value.
 */
long long			ft_readlonglong(int fd);

/**
 * @brief Reads an unsigned integer from a file descriptor
 * @param fd File descriptor to read from
 * @return The unsigned integer value read from the file descriptor
 *
 * This function reads binary data from the file descriptor and
 * interprets it as an unsigned integer value.
 */
unsigned int		ft_readuint(int fd);

/**
 * @brief Reads an unsigned long integer from a file descriptor
 * @param fd File descriptor to read from
 * @return The unsigned long integer value read from the file descriptor
 *
 * This function reads binary data from the file descriptor and
 * interprets it as an unsigned long integer value.
 */
unsigned long		ft_readulong(int fd);

/**
 * @brief Reads an unsigned long long integer from a file descriptor
 * @param fd File descriptor to read from
 * @return The unsigned long long integer value read from the file descriptor
 *
 * This function reads binary data from the file descriptor and
 * interprets it as an unsigned long long integer value.
 */
unsigned long long	ft_readullong(int fd);

/**
 * @brief Reads a string of specified length from a file descriptor
 * @param fd File descriptor to read from
 * @param len Number of characters to read
 * @return Pointer to the newly allocated string, or NULL on failure
 *
 * This function reads exactly 'len' characters from the file descriptor
 * and returns them as a null-terminated string. The caller is responsible
 * for freeing the returned string.
 */
char				*ft_readstr(int fd, int len);

/**
 * @struct s_file
 * @brief Structure representing a file with path and file descriptor
 *
 * This structure encapsulates file information including the file path
 * and its associated file descriptor. It's commonly used for temporary
 * file management and file operations.
 */
typedef struct s_file
{
	// Path to the file
	char			*path;
	// File descriptor for the opened file
	int				fd;
}					t_file;

/// @brief Creates a temporary file with optional automatic unlinking
/// @param rand_fd File descriptor for random number generation
/// @param auto_unlink If true,
/// the file will be automatically unlinked after creation
/// @return Pointer to a t_file structure representing the temporary file,
/// or NULL on failure
///
/// This function creates a temporary file using the provided
/// random file descriptor
/// to generate a unique filename. If auto_unlink is true,
/// the file will be unlinked immediately after creation,
/// making it accessible only through the file descriptor.
/// The caller is responsible for freeing the returned t_file structure.
t_file				*ft_opentmp(int rand_fd, bool auto_unlink);

void				print_prompt(t_list *env);

#endif
