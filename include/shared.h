/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:24:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/05 11:54:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "libft.h"
# include <stdbool.h>
# include <stdint.h>

extern const int	g_status_code;

/// @brief The structure to hold the environment variables
/// @note This structure is used to create a linked list
///       of environment variables
typedef struct s_env
{
	/// @brief The key of the environment variable
	char			*key;
	/// @brief The value of the environment variable
	char			*value;
}					t_env;

/// @brief Check if the environment variable exists in the list
/// @param key The key of the environment variable
/// @return true if the environment variable exists, false otherwise
bool				b_varexists(const char *key, t_list *envp);

/// @brief Get the value of the environment variable
/// @param key The key of the environment variable
/// @return The value of the environment variable, or NULL if not set
/// @note The caller is responsible for freeing the returned string
char				*b_getenv(const char *key, t_list *envp);

/// @brief Set the value of the environment variable
/// @param key The key of the environment variable
/// @param value The value to set
/// @note The caller is responsible for freeing the value string
///       if it was dynamically allocated
void				b_setenv(const char *key, const char *value, t_list *envp);

/// @brief Unset the environment variable
/// @param key The key of the environment variable
/// @param del The function to call to delete the value
/// @note The caller is responsible for setting the correct delete function
void				b_unsetenv(const char *key, void (*del)(void *),
						t_list *envp);

t_list				*b_fromenvp(char *const *envp);

typedef enum e_command_type
{
	COMMAND_COMMAND,          // A command to be executed
	COMMAND_BUILTIN,          // A builtin command (e.g., cd, exit)
	COMMAND_PIPE,             // A pipe component
	COMMAND_REDIRECT_IN,      // A redirection from a file
	COMMAND_REDIRECT_OUT,     // A redirection to a file
	COMMAND_REDIRECT_APPEND,  // A append redirection
	COMMAND_REDIRECT_HEREDOC, // A heredoc redirection
	COMMAND_AND,              // A component of an AND operation `BONUS_ONLY`
	COMMAND_OR,               // A component of an OR operation  `BONUS_ONLY`
}					t_command_type;

typedef struct s_command
{
	char *name;  // The name of the command
	char **args; // The arguments for the command
}					t_command;

typedef struct s_builtin
{
	int				(*cmd)(struct s_builtin *ctx);
	t_list			*envp;
	int fd_in;   // pipe input
	int fd_out;  // pipe output
	int fd_err;  // pipe error
	char **args; // The arguments for the builtin command
}					t_builtin;

typedef union u_command_data
{
	t_command command; // A command to be executed
	t_builtin builtin; // A builtin command (e.g., cd, exit)
	char *pipe;        // A pipe component
	char *redirect;    // A redirection component
	void *and_or;      // A component of an AND or OR operation `BONUS_ONLY`
}					t_command_data;

typedef struct s_cmd_token
{
	t_command_type type; // The type of the command token
	t_command_data data; // The data associated with the command token
}					t_cmd_token;

#endif