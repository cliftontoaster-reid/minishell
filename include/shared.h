/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:24:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/22 13:42:13 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "libft.h"
# include "parser.h"
# include "reader.h"
# include <stdbool.h>
# include <stdint.h>

# define NO_EXIT -1

typedef struct s_reader	t_reader;

extern int				g_status_code;

/// @brief The structure to hold the environment variables
/// @note This structure is used to create a linked list
///       of environment variables
typedef struct s_env
{
	/// @brief The key of the environment variable
	char				*key;
	/// @brief The value of the environment variable
	char				*value;
}						t_env;

/// @brief Check if the environment variable exists in the list
/// @param key The key of the environment variable
/// @return true if the environment variable exists, false otherwise
bool					b_varexists(const char *key, t_list *envp);

/// @brief Get the value of the environment variable
/// @param key The key of the environment variable (if NULL, returns all)
/// @return Array of strings: single value if key found, all env vars if NULL
/// @note The caller is responsible for freeing the returned array and strings
char					**b_getenv(const char *key, t_list *envp);

/// @brief Set the value of the environment variable
/// @param key The key of the environment variable
/// @param value The value to set
/// @note The caller is responsible for freeing the value string
///       if it was dynamically allocated
void					b_setenv(const char *key, const char *value,
							t_list **envp);

/// @brief Unset the environment variable
/// @param key The key of the environment variable
/// @param del The function to call to delete the value
/// @note The caller is responsible for setting the correct delete function
void					b_unsetenv(const char *key, void (*del)(void *),
							t_list **envp);

t_list					*b_fromenvp(char *const *envp);

typedef struct s_cmd
{
	bool				is_pipe;
	int					error;
	int					pid;
	int					argc;
	int					cmdnbr;
	int					fd_infile;
	int					fd_outfile;
	int					**pipes;
	int					fd[2];
	char				**args;
	char				**cmdpathlist;
	char				*redirect_in;
	char				*redirect_out;
	char				*redirect_append;
	char				*redirect_heredoc;
	t_list				*heredoc_delimiters;

	t_list				*var_list;
}						t_cmd;

/// @brief Structure to hold variable expansion processing state
/// @note Used during command argument variable expansion
typedef struct s_varexp
{
	t_list				*vl_node;
	size_t				cmd_idx;
	t_list				*vl;
	int					n;
	int					vi;
	t_list				*it;
	t_list				*inner;
	t_list				*next;
}						t_varexp;

// pipex/ft_pipex.c
void					ft_pipex(t_cmd *cmd, t_list *tenvp, t_reader *reader);

// pipex/cmd_path.c
void					ft_free_split(char **split);

// pipex/ft_error.c
void					ft_cmdpathlist(t_cmd *cmd, t_list *tenvp);
int						ft_check_if_builtin(t_cmd *cmd, int cmd_idx);

// pipex/ft_utils.c
void					closefd(t_cmd *cmd, int exitnbr, t_reader *reader);
void					ft_cleanup_cmd(t_cmd *cmd);
int						ft_nbrofcmds(t_cmd *cmd);

// pipex/ft_builtin.c
void					is_builtin(t_cmd **cmd, t_list **env, int idx,
							t_reader *e);

// base_commands/(...).c
void					ft_cd(char **argv, t_list **envp);
void					ft_echo(int argc, char **argv);
void					ft_env(t_list **env);
void					ft_exit(char **s, t_reader *reader, t_cmd **cmd);
void					ft_export(char **argv, t_list **envp);
void					ft_pwd(t_list **envp);
void					ft_unset(char **args, t_list **envp);

#endif
