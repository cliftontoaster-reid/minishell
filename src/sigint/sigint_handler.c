/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:11:33 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/11 15:37:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "libft.h"
#include "shared.h"
#include "sigint.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig) {
  if (sig == SIGINT) {
    g_status_code = 130;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
  } else if (sig == SIGQUIT) {
  }
}
