/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_places.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:25:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:30:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>

int	num_places(int n)
{
	int	count;

	if (n == 0)
		return (1);
	if (n < 0)
	{
		if (n == INT_MIN)
			n = INT_MAX;
		else
			n = -n;
	}
	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}
