/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 13:38:50 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "git.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

#define COLOUR_RESET "\001\033[0m\002"
#define COLOUR_YELLOW "\001\033[33m\002"
#define COLOUR_RED "\001\033[31m\002"
#define COLOUR_PINK "\001\033[35m\002"

void	git_message(void)
{
	char	*branch;
	bool	uncommitted_changes;
	bool	staged_changes;

	branch = git_getbranch();
	if (branch)
	{
		ft_putstr_fd(" (git: " COLOUR_YELLOW, STDOUT_FILENO);
		ft_putstr_fd(branch, STDOUT_FILENO);
		uncommitted_changes = is_git_changes();
		staged_changes = is_git_changes_staged();
		if (uncommitted_changes || staged_changes)
			ft_putstr_fd(COLOUR_PINK "*", STDOUT_FILENO);
		if (uncommitted_changes)
			ft_putstr_fd(COLOUR_RED "!", STDOUT_FILENO);
		ft_putstr_fd(COLOUR_RESET ")", STDOUT_FILENO);
		free(branch);
	}
}
