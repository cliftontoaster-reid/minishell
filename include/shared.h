/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:24:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/11 12:00:18 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "libft.h"
# include <stdbool.h>
# include <stdint.h>

extern int			g_status_code;

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
						t_list **envp);

t_list				*b_fromenvp(char *const *envp);

typedef enum e_command_type
{
	/* A command to be executed */
	COMMAND_COMMAND,
	/* A builtin command (e.g., cd, exit) */
	COMMAND_BUILTIN,
	/* A pipe component */
	COMMAND_PIPE,
	/* A redirection from a file */
	COMMAND_REDIRECT_IN,
	/* A redirection to a file */
	COMMAND_REDIRECT_OUT,
	/* A append redirection */
	COMMAND_REDIRECT_APPEND,
	/* A heredoc redirection */
	COMMAND_REDIRECT_HEREDOC,
	/* A component of an AND operation `BONUS_ONLY` */
	COMMAND_AND,
	/* A component of an OR operation `BONUS_ONLY` */
	COMMAND_OR,
}					t_command_type;

typedef struct s_command
{
	// The name of the command
	char			*name;
	// The arguments for the command
	char			**args;
}					t_command;

// Forward declaration
struct s_builtin;

typedef int			*(*t_cmd_func)(struct s_builtin *ctx);

typedef struct s_builtin
{
	// The function pointer to the command
	t_cmd_func		cmd;
	// The environement variables
	t_list			*envp;
	// pipe input
	int				fd_in;
	// pipe output
	int				fd_out;
	// pipe error
	int				fd_err;
	// The arguments for the builtin command
	char			**args;
}					t_builtin;

/// @brief Returns the command function associated with the string
/// @param cmd The command string
/// @return The function pointer to the command, or NULL if not found
t_cmd_func			b_get_command_func(const char *cmd);

typedef union u_command_data
{
	// A command to be executed
	t_command		command;
	// A builtin command (e.g., cd, exit)
	t_builtin		builtin;
	// A pipe component
	bool			pipe;
	// A redirection component
	char			*redirect;
	// A component of an AND or OR operation `BONUS_ONLY`
	bool			and_or;
}					t_command_data;

typedef struct s_cmd_token
{
	// The type of the command token
	t_command_type	type;
	// The data associated with the command token
	t_command_data	data;
}					t_cmd_token;

#endif