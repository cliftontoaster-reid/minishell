/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:42:35 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/24 13:01:26 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#define SUCCESS 0
#define FAILURE 1

/// @brief Allocates the main structure of reader
///
/// @return A pointer to a malloced `t_reader`
static t_reader	*allocate_reader(void)
{
	t_reader	*reader;

	reader = ft_calloc(1, sizeof(t_reader));
	if (reader == NULL)
		errno = ENOMEM;
	return (reader);
}

/// @brief Initalizes the environement variables
///
/// Unless `envp == NULL`, the variable `reader->env`
/// is left NULL for it to be made a default value
/// later on.
///
/// @param reader The main reader structure pointer
/// @param envp The environement variables sent by C
/// @return `1` if an error occured, `0` otherwise.
static int	initialize_env(t_reader *reader, char *const *envp)
{
	if (envp == NULL || *envp == NULL)
	{
		reader->env = NULL;
		return (SUCCESS);
	}
	reader->env = b_fromenvp(envp);
	if (reader->env == NULL)
	{
		free(reader);
		errno = ENOMEM;
		return (FAILURE);
	}
	return (SUCCESS);
}

/// @brief Allocates memory to the line reader
/// @param reader The main reader structure pointer
/// @return `1` if an error occured, `0` otherwise
static int	initialize_linereader(t_reader *reader)
{
	reader->linereader = ft_calloc(1, sizeof(t_linereader));
	if (reader->linereader == NULL)
	{
		ft_lstclear(&reader->env, free);
		free(reader);
		errno = ENOMEM;
		return (FAILURE);
	}
	return (SUCCESS);
}

/// @brief Allocates all memory needed to start minishell
/// and set unused fields to `NULL`
///
/// @param envp The environement variables sent by C
/// @return A pointer to a malloced `t_reader`
t_reader	*reader_init(char *const *envp)
{
	t_reader	*reader;

	reader = allocate_reader();
	if (reader == NULL)
		return (NULL);
	if (initialize_env(reader, envp))
		return (NULL);
	if (initialize_linereader(reader))
		return (NULL);
	reader->cached_input = NULL;
	reader->commands = NULL;
	reader->varnames = NULL;
	return (reader);
}
