/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 19:51:05 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "reader.h"
#include "utils.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

#define PROMPT "picoshell> "

static inline void	add_stuff_to_history(t_reader *r, char *input)
{
	if (!input || *input == '\0' || (r->history_last
			&& str_equal(r->history_last, input)))
		return ;
	add_history(input);
	if (r->history_file > STDERR_FILENO)
		ft_putendl_fd(input, r->history_file);
	free(r->history_last);
	r->history_last = ft_strdup(input);
}

int	read_input(t_reader *reader_ptr)
{
	print_prompt(reader_ptr->env);
	reader_ptr->cached_input = readline(PROMPT);
	if (str_is_whitespace(reader_ptr->cached_input))
	{
		g_status_code = 0;
		return (2);
	}
	add_stuff_to_history(reader_ptr, reader_ptr->cached_input);
	if (!reader_ptr->cached_input)
	{
		if (errno == EINTR)
			return (1);
		write(1, "exit\n", 5);
		return (0);
	}
	return (2);
}
