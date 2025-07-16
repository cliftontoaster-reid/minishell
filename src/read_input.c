/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:15:21 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "utils.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

#define PROMPT "picoshell> "

int	read_input(t_reader *reader_ptr)
{
	print_prompt(reader_ptr->env);
	reader_ptr->cached_input = readline(PROMPT);
	add_history(reader_ptr->cached_input);
	if (!reader_ptr->cached_input)
	{
		if (errno == EINTR)
			return (1);
		write(1, "exit\n", 5);
		return (0);
	}
	return (2);
}
