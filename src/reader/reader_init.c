/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:42:35 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/22 13:34:49 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static t_reader	*allocate_reader(void)
{
	t_reader	*reader;

	reader = ft_calloc(1, sizeof(t_reader));
	if (reader == NULL)
		errno = ENOMEM;
	return (reader);
}

static int	initialize_env(t_reader *reader, char *const *envp)
{
	reader->env = b_fromenvp(envp);
	if (reader->env == NULL)
	{
		free(reader);
		errno = ENOMEM;
		return (0);
	}
	return (1);
}

static int	initialize_linereader(t_reader *reader)
{
	reader->linereader = ft_calloc(1, sizeof(t_linereader));
	if (reader->linereader == NULL)
	{
		ft_lstclear(&reader->env, free);
		free(reader);
		errno = ENOMEM;
		return (0);
	}
	return (1);
}

t_reader	*reader_init(char *const *envp)
{
	t_reader	*reader;

	reader = allocate_reader();
	if (reader == NULL)
		return (NULL);
	if (!initialize_env(reader, envp))
		return (NULL);
	if (!initialize_linereader(reader))
		return (NULL);
	reader->cached_input = NULL;
	reader->commands = NULL;
	reader->varnames = NULL;
	return (reader);
}
