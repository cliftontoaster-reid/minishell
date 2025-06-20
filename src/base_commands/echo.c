/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:24:35 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/18 09:56:48 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>

static void	ft_echo_screen(int argc, char **argv, int newline, int iter)
{
	while (iter<argc)
	{
		write(1, argv[iter], strlen(argv[iter])); //---------- strlen TODO
		iter++;
		if (iter<argc)
			write(1, " ", 1);
		else if (newline)
			write(1, "\n", 1);
	}
}

void	ft_echo(int argc, char **argv) /*, t_list *tenvp)*/
{
	int		iter;
	int		iter_s;
	char	newline;

	newline = 1;
	iter = 1;
	while (iter<argc)
	{
		iter_s = 2;
		if (!strncmp(argv[iter], "-n", 2)) //------------------- strncmp TODO
		{
			while (argv[iter][iter_s] == 'n')
				iter_s++;
			if (!argv[iter][iter_s])
			{
				newline = 0;
				iter++;
			}
			else
				break ;
		}
		else
			break ;
	}
	ft_echo_screen(argc, argv, newline, iter);
}

int	main(int argc, char **argv) /*, t_list *tenvp)*/
{
	if (argc > 1)
		ft_echo(argc, argv); /*, t_list *tenvp);*/
	else
		write(1, "\n", 1);
	return (0);
}
