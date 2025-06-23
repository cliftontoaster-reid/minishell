/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:28 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/23 16:07:21 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "reader.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	lst_list(char **lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst[i])
		i++;
	return (i);
}

bool	isstring_noomber(char *s)
{
	if (!s || !*s)
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

void	ft_exit(char *s, t_reader *reader)
{
	int	exit_code;

	if (!s || !*s)
	{
		return ;
	}
	if (lst_list(s) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	// Check if the string is a valid number
	if (s[1] && !isstring_noomber(s[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return ;
	}
	exit_code = 0;
	if (s[1])
	{
		exit_code = ft_atoi(s[1]);
		if (exit_code < 0 || exit_code > 255)
		{
			ft_putstr_fd("exit: exit code out of range (0-255)\n", 2);
			exit_code = 255; // Set to a default exit code
		}
	}
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
