/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_whitespace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 14:23:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

bool	str_is_whitespace(const char *str)
{
	if (str == NULL)
		return (false);
	while (*str)
	{
		if (!ft_ciswhite(*str))
			return (false);
		str++;
	}
	return (true);
}
