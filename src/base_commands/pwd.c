/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:55:23 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/23 11:52:33 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	ft_pwd(void)
{
	char	pwd[420];

	getcwd(pwd, 419);
	if (pwd[0])
	{
		printf("%s\n", pwd);
		g_status_code = 0;
	}
	else
	{
		write(2, "pwd: error retrieving current directory\n", 40);
		g_status_code = 1;
	}
}
