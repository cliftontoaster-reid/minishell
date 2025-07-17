/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:53 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/17 10:41:47 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

void	handle_read(t_reader *reader, const char *input)
{
	if (reader == NULL || input == NULL)
	{
		errno = EINVAL;
		return ;
	}
	if (!try_read(reader, input))
	{
		errno = ENOMEM;
		return ;
	}
	if (str_is_whitespace(reader->cached))
	{
		free(reader->cached);
		reader->cached = NULL;
		g_status_code = 0;
		return ;
	}
	if (handle_read_two(reader))
		return ;
	free(reader->cached);
	reader->cached = NULL;
}
