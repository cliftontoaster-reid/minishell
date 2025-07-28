/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:28 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/28 10:42:10 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "reader.h"
#include <readline/history.h>
#include <stdlib.h>
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
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

static void	exit_exec(int exit_code, t_reader *reader)
{
	if (reader)
		reader_free(reader);
	clear_history();
	write(1, "exit\n", 5);
	exit(exit_code);
}

void	ft_exit(char **s, t_reader *reader, t_cmd **cmd)
{
	unsigned char	exit_code;

	(void)cmd;
	if (!s || !*s)
		return ;
	if (lst_list(s) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	if (s[1] && !isstring_noomber(s[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit_code = 2;
		exit_exec(exit_code, reader);
	}
	exit_code = 0;
	if (s[1])
		exit_code = ft_atoi(s[1]);
	exit_exec(exit_code, reader);
}
