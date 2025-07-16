/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_branch_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:07:19 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "git.h"
#include "libft.h"

char	*get_branch_name(char *buffer, ssize_t n)
{
	char	*newline;
	size_t	len;

	if (ft_strncmp(buffer, "ref: refs/heads/", 16) == 0)
	{
		newline = ft_strchr(buffer, '\n');
		if (newline)
			len = (size_t)(newline - (buffer + 16));
		else
			len = (size_t)(n - 16);
		return (ft_strndup(buffer + 16, len));
	}
	else
	{
		if (n > 7)
			return (ft_strndup(buffer, 7));
		else
			return (ft_strndup(buffer, (size_t)n));
	}
}
