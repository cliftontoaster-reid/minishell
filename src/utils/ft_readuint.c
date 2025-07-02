/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readuint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:41:49 by creid             #+#    #+#             */
/*   Updated: 2025/07/02 12:54:55 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

unsigned int	ft_readuint(int fd)
{
	unsigned int	value;

	if (read(fd, &value, sizeof(unsigned int)) != sizeof(unsigned int))
		return (0);
	return (value);
}
