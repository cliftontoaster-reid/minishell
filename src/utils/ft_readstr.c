/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:41:49 by creid             #+#    #+#             */
/*   Updated: 2025/07/02 14:40:19 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 256

static char	get_random_alpha_buffered(unsigned char *buffer, int *pos,
		int *remaining, int fd)
{
	unsigned char	rand_byte;
	int				idx;

	if (*remaining <= 0)
	{
		*remaining = read(fd, buffer, BUFFER_SIZE);
		*pos = 0;
		if (*remaining <= 0)
			return ('a');
	}
	rand_byte = buffer[*pos];
	(*pos)++;
	(*remaining)--;
	idx = rand_byte % 52;
	if (idx < 26)
		return ('A' + idx);
	else
		return ('a' + (idx - 26));
}

char	*ft_readstr(int fd, int len)
{
	char			*str;
	unsigned char	buffer[BUFFER_SIZE];
	int				i;
	int				buffer_pos;
	int				buffer_remaining;

	if (len <= 0)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	buffer_pos = 0;
	buffer_remaining = 0;
	i = 0;
	while (i < len)
	{
		str[i] = get_random_alpha_buffered(buffer, &buffer_pos,
				&buffer_remaining, fd);
		i++;
	}
	str[len] = '\0';
	return (str);
}
