/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_unmatched_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:25:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:26:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>

size_t	count_unmatched_var(char *str, size_t i)
{
	size_t	count;

	count = 1;
	while (iskey(str[i]))
	{
		count++;
		i++;
	}
	return (count);
}
