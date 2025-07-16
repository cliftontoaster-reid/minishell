/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_repo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 13:38:50 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "git.h"
#include <stdlib.h>

// Check if current directory is inside a git repository
bool	is_repo(void)
{
	char	*gd;

	gd = find_git_dir();
	if (gd)
	{
		free(gd);
		return (true);
	}
	return (false);
}
