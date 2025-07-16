/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_regular_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:40:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:44:41 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	copy_regular_char(char *dest, char *src, size_t *i, size_t k)
{
	dest[k] = src[*i];
	(*i)++;
	return (k + 1);
}
