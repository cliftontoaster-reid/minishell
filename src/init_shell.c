/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 20:09:39 by lfiorell@st      ###   ########.fr       */
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

char	*get_history_file_path(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	return (ft_strjoin(home, "/" HISTORY_FILE));
}

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

t_reader	*init_shell(char **envp)
{
	t_reader	*reader_ptr;

	reader_ptr = reader_init(envp);
	load_history_file(reader_ptr);
	rl_catch_signals = 0;
	register_reader();
	return (reader_ptr);
}
