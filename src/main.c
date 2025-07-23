/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:49:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 14:55:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include "reader.h"
#include "shared.h"
#include "varextract.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <string.h>
#include <unistd.h>

void	default_env(t_reader *reader)
{
	char	cwd[420];

	if (reader->env == NULL)
	{
		getcwd(cwd, 419);
		b_setenv("PWD", cwd, &reader->env);
		b_setenv("SHLVL", "1", &reader->env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_reader	*reader_ptr;
	int			input_status;

	(void)argc;
	(void)argv;
	reader_ptr = init_shell(envp);
	default_env(reader_ptr);
	while (1)
	{
		input_status = read_input(reader_ptr);
		if (input_status == 1)
			continue ;
		if (input_status == 0)
			break ;
		handle_read(reader_ptr, reader_ptr->cached_input);
		free(reader_ptr->cached_input);
		reader_ptr->cached_input = NULL;
		if (reader_ptr->parser)
			process_commands(reader_ptr);
		cleanup_iteration(reader_ptr);
	}
	cleanup_shell(reader_ptr);
	return (g_status_code);
}
