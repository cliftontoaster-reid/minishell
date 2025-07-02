/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:41:49 by creid             #+#    #+#             */
/*   Updated: 2025/07/02 12:55:45 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_readstr(int fd, int len)
{
	char	*str;
	ssize_t	bytes_read;

	if (len <= 0)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	bytes_read = read(fd, str, len);
	if (bytes_read < 0)
	{
		free(str);
		return (NULL);
	}
	str[bytes_read] = '\0';
	return (str);
}
