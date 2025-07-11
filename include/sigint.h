/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:33:51 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/11 15:17:27 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGINT_H
# define SIGINT_H

# include "reader.h"
# include <signal.h>

void	sigint_handler(int sig);

void	register_reader(void);

#endif
