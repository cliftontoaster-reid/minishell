/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/24 12:59:26 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "sigint.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define HISTORY_FILE ".picoshell_history"

/// @brief Returns a string containing $HOME/.picoshell_history
/// 
/// @return A valid ACII string or NULL if HOME is not in the environement 
char	*get_history_file_path(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	return (ft_strjoin(home, "/" HISTORY_FILE));
}

/// @brief Reads from fd and puts every line of the file to history
/// @param fd The file descriptor for the history file.
/// @param reader The main reader structure pointer
void	read_fluff_history(int fd, t_reader *reader)
{
	char	*buffer;
	char	*line;

	buffer = NULL;
	while (1)
	{
		line = get_next_line(fd, &buffer);
		if (!line)
			break ;
		add_history(line);
		if (reader->history_last)
			free(reader->history_last);
		reader->history_last = ft_strdup(line);
		free(line);
	}
	if (buffer)
		free(buffer);
}

/// @brief Opens and reads the history if possible
/// then opens it again for appending to/creating the new history
///
/// ### Warning
///
/// If it fails to create or get the path to the history file
/// no error will be raised, the shell will simply not write
/// to an history file further on.
///
/// @param reader The main reader structure pointer
void	load_history_file(t_reader *reader)
{
	char	*history_path;

	history_path = get_history_file_path();
	if (history_path)
	{
		reader->history_file = open(history_path, O_RDONLY);
		if (reader->history_file >= 0)
		{
			read_fluff_history(reader->history_file, reader);
			close(reader->history_file);
		}
		reader->history_file = open(history_path, O_WRONLY | O_APPEND | O_CREAT,
				0644);
		free(history_path);
	}
	else
		reader->history_file = -1;
}

/// @brief Initializes the shell environement, including env variables,
/// as well as the necessary allocs to store the future data used by the shell.
///
/// ### Reader signal handling
///
/// The `rl_catch_signals = 0;`line is used so that readline does not attempt
/// to handle signals on its own.
///
/// @param envp The environement variables sent by C
/// @return The main reader structure pointer
t_reader	*init_shell(char **envp)
{
	t_reader	*reader_ptr;

	reader_ptr = reader_init(envp);
	load_history_file(reader_ptr);
	rl_catch_signals = 0;
	register_reader();
	return (reader_ptr);
}
