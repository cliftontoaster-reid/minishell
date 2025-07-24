/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_reader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:09:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/24 12:57:32 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "shared.h"
#include "sigint.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>

/// @brief Registers all the signals and their actions through sigaction.
void	register_reader(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, NULL);
}
