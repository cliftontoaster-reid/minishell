/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:49:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:08:13 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "main_extra.h"
#include "parser.h"
#include "reader.h"
#include "shared.h"
#include "sigint.h"
#include "utils.h"
#include "varextract.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	t_reader	*reader_ptr;
	int			input_status;

	(void)argc;
	(void)argv;
	reader_ptr = init_shell(envp);
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
