/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:28 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/23 11:01:33 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "reader.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_exit(char *s, t_reader *reader)
{
	int	iteri;

	iteri = 0;
	while (s[iteri])
		if (!ft_isdigit(s[iteri++])) //------------	TODO isdigit !!!
			*s = '2';
	// Free the reader resources
	if (reader)
	{
		if (reader->cached)
			free(reader->cached);
		if (reader->lexer)
			free_lexer(reader->lexer);
		if (reader->tokens)
		{
			ft_lstclear(&reader->tokens, (void (*)(void *))free_token);
			reader->tokens = NULL;
		}
		if (reader->parser)
			parser_free(reader->parser);
		free(reader);
	}
	exit(atoi(s)); //--------------------------	TODO atoi !!!
	while (1)
		write(1, "loser ", 6);
}
