/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openrand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:42:11 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/02 11:43:05 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	ft_openrand(void)
{
	int	fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening /dev/random");
		return (-1);
	}
	return (fd);
}
