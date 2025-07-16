/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:31:30 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/16 15:48:17 by lfiorell@st      ###   ########.fr       */
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
# include <fcntl.h>
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

/// @brief Expands a variable string by replacing variable names with their values
/// @param var The input variable string
/// @param varnames Array of variable names
/// @param env The environment list
/// @return A newly allocated string with expanded variable values,
/// or NULL on failure
char				*ft_var(char *var, char **varnames, t_list *env);

/// @brief Finds and returns the PID of the current process
/// @return The process ID of the current process
pid_t				b_getpid(void);

/**
 * @struct s_var_match
 * @brief Structure to hold variable matching information
 *
 * This structure encapsulates the result of a variable name search,
 * including whether a match was found, the length of the matched variable name,
 * and the value of the matched variable.
 */
typedef struct s_var_match
{
	bool found;  // Whether a variable match was found
	int var_len; // Length of the matched variable name
	char *value; // Value of the matched variable
}					t_var_match;

/**
 * @struct s_var_context
 * @brief Structure to encapsulate variable substitution context
 *
 * This structure contains all the parameters commonly passed to variable
 * substitution functions, reducing function parameter count and improving
 * code maintainability.
 */
typedef struct s_var_context
{
	char *dest;      // Destination buffer
	char *src;       // Source string
	size_t *i;       // Pointer to current index in source
	size_t k;        // Current position in destination buffer
	char **varnames; // Array of variable names
	t_list *env;     // Environment list
	size_t len;      // Total length of destination buffer (when needed)
}					t_var_context;

/// @brief Gets a single environment variable value
/// @param name The name of the environment variable
/// @param env The environment list
/// @return The value of the environment variable, or NULL if not found
char				*b_getenv_one(char *name, t_list *env);

/// @brief Finds a variable match in the provided variable names
/// @param str_pos Position in string to start matching from
/// @param varnames Array of variable names to search
/// @param env The environment list
/// @return A t_var_match structure containing match information
t_var_match			find_var_match(char *str_pos, char **varnames, t_list *env);

/// @brief Handles special variables like $? and $$
/// @param c The special variable character ('?' or '$')
/// @return The length of the special variable value as string
size_t				handle_special_var(char c);

/// @brief Counts the length of an unmatched variable
/// @param str The input string
/// @param i Starting index in the string
/// @return The count of characters in the unmatched variable
size_t				count_unmatched_var(char *str, size_t i);

/// @brief Copies a string from source to destination
/// @param dest Destination buffer
/// @param src Source string
void				ft_strcpy(char *dest, const char *src);

/// @brief Expands a matched variable into the destination string
/// @param dest Destination buffer
/// @param match The variable match information
/// @param k Current position in destination buffer
/// @return Updated position in destination buffer
size_t				expand_matched_var(char *dest, t_var_match match, size_t k);

/// @brief Expands an unmatched variable into the destination string
/// @param dest Destination buffer
/// @param src Source string
/// @param i Current position in source string
/// @param k Current position in destination buffer
/// @return Updated position in destination buffer
size_t				expand_unmatched_var(char *dest, char *src, size_t i,
						size_t k);

/// @brief Expands a special variable into the destination string
/// @param dest Destination buffer
/// @param c The special variable character
/// @param k Current position in destination buffer
/// @param len Total length of destination buffer
/// @return Updated position in destination buffer
size_t				expand_special_var(char *dest, char c, size_t k,
						size_t len);

/// @brief Checks if a character is a valid variable key character
/// @param c The character to check
/// @return true if the character is valid for variable names, false otherwise
bool				iskey(char c);

/// @brief Calculates the number of digits in an integer
/// @param n The integer to count digits for
/// @return The number of digits in the integer
int					num_places(int n);

/// @brief Handles regular character processing for variable expansion
/// @param i Pointer to current index position
/// @return The length contribution (1 for regular characters)
size_t				handle_regular_char(size_t *i);

/// @brief Handles variable expansion during length calculation
/// @param str The input string
/// @param i Pointer to current index position
/// @param varnames Array of variable names
/// @param env The environment list
/// @return The length of the expanded variable
size_t				handle_var_expansion(char *str, size_t *i, char **varnames,
						t_list *env);

/// @brief Handles dollar character processing during length calculation
/// @param str The input string
/// @param i Pointer to current index position
/// @param varnames Array of variable names
/// @param env The environment list
/// @return The length contribution from the dollar character processing
size_t				handle_dollar_char(char *str, size_t *i, char **varnames,
						t_list *env);

/// @brief Copies a regular character during variable substitution
/// @param dest Destination buffer
/// @param src Source string
/// @param i Pointer to current index in source
/// @param k Current position in destination buffer
/// @return Updated position in destination buffer
size_t				copy_regular_char(char *dest, char *src, size_t *i,
						size_t k);

/// @brief Handles variable substitution during string building
/// @param ctx Variable context containing all necessary parameters
/// @return Updated position in destination buffer
size_t				handle_var_substitution(t_var_context *ctx);

/// @brief Handles dollar character substitution during string building
/// @param ctx Variable context containing all necessary parameters
/// @return Updated position in destination buffer
size_t				handle_dollar_substitution(t_var_context *ctx);

/// @brief Replaces backspace characters with dollar signs
/// @param str String to process
void				replace_backspace_with_dollar(char *str);

#endif
