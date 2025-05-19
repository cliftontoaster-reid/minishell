/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:24:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/19 14:27:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>

const int		g_status_code = 0;

/// @brief The structure to hold the environment variables
/// @note This structure is used to create a linked list
///       of environment variables
typedef struct s_env
{
	/// @brief The key of the environment variable
	char		*key;
	/// @brief The value of the environment variable
	char		*value;
	/// @brief The next environment variable in the list
	t_env		*next;
}				t_env;

/// @brief Check if the environment variable exists in the list
/// @param key The key of the environment variable
/// @return true if the environment variable exists, false otherwise
bool			varexists(const char *key);

/// @brief Get the value of the environment variable
/// @param key The key of the environment variable
/// @return The value of the environment variable, or NULL if not set
/// @note The caller is responsible for freeing the returned string
char			*getenv(const char *key);

/// @brief Set the value of the environment variable
/// @param key The key of the environment variable
/// @param value The value to set
/// @note The caller is responsible for freeing the value string
///       if it was dynamically allocated
void			setenv(const char *key, const char *value);

/// @brief Unset the environment variable
/// @param key The key of the environment variable
/// @param del The function to call to delete the value
/// @note The caller is responsible for setting the correct delete function
void			unsetenv(const char *key, void (*del)(void *));

/// @brief The different types of arguments that can be passed to a command
/// @note This is used to determine how to handle the argument
typedef enum e_argtype
{
	/// @brief No argument, should be ignored
	ARG_NONE = 0,
	/// @brief A string argument, should be passed as is
	ARG_STRING,
	/// @brief A key value pair argument, it should be taken from env
	ARG_VAR,
	/// @brief A status argument, it should be taken from `g_status_code`
	ARG_STATUS,
}				t_argtype;

/// @brief The different types of commands that can be executed
/// @note This is used to determine how to handle the command
typedef struct s_argument
{
	/// @brief The type of the argument
	t_argtype	type;
	/// @brief The key or value of the argument if it is not
	///        `ARG_NONE` or `ARG_STATUS`
	char		*value;
}				t_argument;

/// @brief A structure to hold everything needed to execute a command
typedef struct s_command
{
	/// @brief The command to execute
	char		*name;
	/// @brief The number of arguments
	int			argc;
	/// @brief The arguments to pass to the command
	char		**argv;
	/// @brief The environment variables
	t_env		**envp;

	/// @brief Flags used to determine how to handle the command
	///
	/// @note Functions like `is_builtin`, `has_input_redirect`,
	/// etc. will use these flags to determine
	///
	/// - bit 0 : command is a builtin
	///
	/// - bit 1 : has input redirection
	///
	/// - bit 2 : has output redirection
	///
	/// - bit 3 : has error redirection
	///
	/// - bit 4 : has pipe in
	///
	/// - bit 5 : has pipe out
	///
	/// - bit 6 : soft redirect
	///
	/// - bit 7 : is local
	uint8_t		flags;

	/// @brief The file descriptors from which to read stdin
	int			input_fd;
	/// @brief The file descriptors to which to write stdout
	int			output_fd;
	/// @brief The file descriptors to which to write stderr
	int			error_fd;
}				t_command;

/// @brief Check if the command is a built-in
/// @param cmd The command to check
/// @return true if the command is a built-in, false otherwise
bool			is_builtin(t_command *cmd);

/// @brief Check if the command has input redirection
/// @param cmd The command to inspect
/// @return true if input redirection is set, false otherwise
bool			has_input_redirect(t_command *cmd);

/// @brief Check if the command has output redirection
/// @param cmd The command to inspect
/// @return true if output redirection is set, false otherwise
bool			has_output_redirect(t_command *cmd);

/// @brief Check if the command has error redirection
/// @param cmd The command to inspect
/// @return true if error redirection is set, false otherwise
bool			has_error_redirect(t_command *cmd);

/// @brief Check if the command has a pipe input
/// @param cmd The command to inspect
/// @return true if pipe input is set, false otherwise
bool			has_pipe_in(t_command *cmd);

/// @brief Check if the command has a pipe output
/// @param cmd The command to inspect
/// @return true if pipe output is set, false otherwise
bool			has_pipe_out(t_command *cmd);

/// @brief Check if the command uses a soft redirect
/// @param cmd The command to inspect
/// @return true if soft redirect is set, false otherwise
bool			has_soft_redirect(t_command *cmd);

/// @brief Runs the commands
/// @param cmd The commands to run
/// @return The status code of the command
/// @note This function will execute the command and return the status code
int				run_commands(t_command *cmd);
