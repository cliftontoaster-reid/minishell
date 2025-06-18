/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:42:35 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/17 11:23:17 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

t_reader	*reader_init(char *const *envp)
{
	t_reader	*reader;

	reader = ft_calloc(1, sizeof(t_reader));
	if (reader == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	reader->env = b_fromenvp(envp);
	if (reader->env == NULL)
	{
		free(reader);
		errno = ENOMEM;
		return (NULL);
	}
	return (reader);
}
