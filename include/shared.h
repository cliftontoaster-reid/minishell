/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:24:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/20 15:29:08 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include "libft.h"
# include <stdbool.h>
# include <stdint.h>

extern int	g_status_code;

/// @brief The structure to hold the environment variables
/// @note This structure is used to create a linked list
///       of environment variables
typedef struct s_env
{
	/// @brief The key of the environment variable
	char	*key;
	/// @brief The value of the environment variable
	char	*value;
}			t_env;

/// @brief Check if the environment variable exists in the list
/// @param key The key of the environment variable
/// @return true if the environment variable exists, false otherwise
bool		b_varexists(const char *key, t_list *envp);

/// @brief Get the value of the environment variable
/// @param key The key of the environment variable
/// @return The value of the environment variable, or NULL if not set
/// @note The caller is responsible for freeing the returned string
char		*b_getenv(const char *key, t_list *envp);

/// @brief Set the value of the environment variable
/// @param key The key of the environment variable
/// @param value The value to set
/// @note The caller is responsible for freeing the value string
///       if it was dynamically allocated
void		b_setenv(const char *key, const char *value, t_list **envp);

/// @brief Unset the environment variable
/// @param key The key of the environment variable
/// @param del The function to call to delete the value
/// @note The caller is responsible for setting the correct delete function
void		b_unsetenv(const char *key, void (*del)(void *), t_list **envp);

t_list		*b_fromenvp(char *const *envp);

typedef struct s_cmd
{
	char	**args;
	int		argc;
	bool	is_pipe;
	int		fd_infile;
	int		fd_outfile;
	char	*redirect_in;
	char	*redirect_out;
	char	*redirect_append;
	char	*redirect_heredoc;
}			t_cmd;

//pipex/ft_pipex.c
void	ft_pipex(t_cmd *cmd, t_list *tenvp);

#endif
