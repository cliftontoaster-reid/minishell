/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:15:21 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "sigint.h"
#include <readline/readline.h>
#include <stdio.h>

t_reader	*init_shell(char **envp)
{
	t_reader	*reader_ptr;

	reader_ptr = reader_init(envp);
	rl_catch_signals = 0;
	register_reader();
	return (reader_ptr);
}
