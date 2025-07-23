/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:41:12 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/23 14:54:51 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main_extra.h"
#include "parser.h"
#include "reader.h"
#include "shared.h"
#include "utils.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

// Helper function to find the last delimiter in the list
static char	*find_last_delimiter(t_list *heredoc_delimiters)
{
	t_list	*delim_node;
	char	*last_delimiter;

	delim_node = heredoc_delimiters;
	last_delimiter = NULL;
	while (delim_node)
	{
		last_delimiter = (char *)delim_node->content;
		delim_node = delim_node->next;
	}
	return (last_delimiter);
}

// Helper function to read heredoc input until delimiter is found
static void	read_heredoc_input(char *delimiter, t_file *tmpf,
		bool write_to_file)
{
	char	*line;

	while (true)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		if (write_to_file && tmpf)
		{
			ft_putstr_fd(line, tmpf->fd);
			ft_putstr_fd("\n", tmpf->fd);
		}
		free(line);
	}
}

// Helper function to process all heredoc delimiters for a command
static t_file	*process_heredoc_delimiters(t_list *heredoc_delimiters)
{
	t_list	*delim_node;
	char	*delimiter;
	char	*last_delimiter;
	t_file	*tmpf;

	last_delimiter = find_last_delimiter(heredoc_delimiters);
	tmpf = NULL;
	delim_node = heredoc_delimiters;
	while (delim_node)
	{
		delimiter = (char *)delim_node->content;
		if (delimiter == last_delimiter)
		{
			tmpf = ft_opentmp(ft_openurand(), true);
			if (!tmpf)
			{
				perror("heredoc");
				break ;
			}
		}
		read_heredoc_input(delimiter, tmpf, delimiter == last_delimiter);
		delim_node = delim_node->next;
	}
	return (tmpf);
}

// Helper function to handle fallback heredoc (backward compatibility)
static t_file	*process_fallback_heredoc(char *redirect_heredoc)
{
	t_file	*tmpf;

	tmpf = ft_opentmp(ft_openurand(), true);
	if (!tmpf)
	{
		perror("heredoc");
		return (NULL);
	}
	read_heredoc_input(redirect_heredoc, tmpf, true);
	return (tmpf);
}

// New: process here-documents for parsed commands
void	process_heredocs(t_cmd *cmds)
{
	size_t	iteri;
	t_file	*tmpf;

	iteri = 0;
	while (cmds[iteri].args)
	{
		tmpf = NULL;
		if (cmds[iteri].heredoc_delimiters)
			tmpf = process_heredoc_delimiters(cmds[iteri].heredoc_delimiters);
		else if (cmds[iteri].redirect_heredoc)
			tmpf = process_fallback_heredoc(cmds[iteri].redirect_heredoc);
		if (tmpf)
		{
			lseek(tmpf->fd, 0, SEEK_SET);
			cmds[iteri].fd_infile = tmpf->fd;
			free(tmpf->path);
			free(tmpf);
		}
		iteri++;
	}
}
