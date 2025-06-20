/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:28 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/16 18:33:04 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>	
#include <stdlib.h>	
#include <ctype.h>	
#include <unistd.h>

void	ft_exit(char *s)
{
	int	iteri;

	iteri = 0;
	while (s[iteri])
		if (!isdigit(s[iteri++])) //------------	TODO isdigit !!!
			*s = '2';
	exit(atoi(s));	//--------------------------	TODO atoi !!!
	while (1)
		write(1, "loser ", 6);
}

int main(int argc, char **argv) 
{
	if (argc == 1)
		ft_exit("0");
	if (argc == 2)
		ft_exit(argv[1]);
	write(1, "exit: too many arguments\n", 25);
	return (1);
}
