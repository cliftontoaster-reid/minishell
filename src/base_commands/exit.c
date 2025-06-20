/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:28 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/20 14:50:11 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_exit(char *s)
{
	int	iteri;

	iteri = 0;
	while (s[iteri])
		if (!ft_isdigit(s[iteri++])) //------------	TODO isdigit !!!
			*s = '2';
	exit(atoi(s)); //--------------------------	TODO atoi !!!
	while (1)
		write(1, "loser ", 6);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		ft_exit("0");
	if (argc == 2)
		ft_exit(argv[1]);
	write(1, "exit: too many arguments\n", 25);
	return (1);
}
