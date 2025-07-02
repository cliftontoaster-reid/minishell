/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openurand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:43:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/02 11:43:49 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	ft_openurand(void)
{
	int	fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening /dev/urandom");
		return (-1);
	}
	return (fd);
}
