/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_matched_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:25:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:26:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stddef.h>

size_t	expand_matched_var(char *dest, t_var_match match, size_t k)
{
	if (match.value != NULL)
	{
		ft_strcpy(&dest[k], match.value);
		k += ft_strlen(match.value);
	}
	return (k);
}
