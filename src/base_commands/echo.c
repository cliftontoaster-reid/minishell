/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:58:57 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/09 11:13:29 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <shared.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void ft_echo_screen(int argc, char **argv, int newline, int iter) {
  while (iter < argc) {
    write(1, argv[iter], ft_strlen(argv[iter]));
    iter++;
    if (iter < argc)
      write(1, " ", 1);
    else if (newline)
      write(1, "\n", 1);
  }
  g_status_code = 0;
}

void ft_echo(int argc, char **argv) {
  int iter;
  int iter_s;
  char newline;

  newline = 1;
  iter = 1;
  while (iter < argc) {
    iter_s = 2;
    if (!ft_strncmp(argv[iter], "-n", 2)) {
      while (argv[iter][iter_s] == 'n')
        iter_s++;
      if (!argv[iter][iter_s]) {
        newline = 0;
        iter++;
      } else
        break;
    } else
      break;
  }
  ft_echo_screen(argc, argv, newline, iter);
}
