/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linereader_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:00:27 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/18 13:03:11 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <errno.h>
#include <stdlib.h>

void	linereader_free(t_linereader *reader)
{
	if (reader == NULL)
		return ;
	if (reader->line)
		free(reader->line);
	free(reader);
	errno = 0;
}
