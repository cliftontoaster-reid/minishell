/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:23:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

bool	try_read(t_reader *reader, const char *input)
{
	char	*new_cached;

	if (reader->cached != NULL)
	{
		new_cached = ft_strjoin(reader->cached, input);
		if (new_cached == NULL)
		{
			errno = ENOMEM;
			return (false);
		}
		free(reader->cached);
		reader->cached = new_cached;
	}
	else
	{
		reader->cached = ft_strdup(input);
		if (reader->cached == NULL)
		{
			errno = ENOMEM;
			return (false);
		}
	}
	return (true);
}
