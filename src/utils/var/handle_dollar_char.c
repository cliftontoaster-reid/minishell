/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:40:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 14:54:08 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	handle_dollar_char(char *str, size_t *i, char **varnames, t_list *env)
{
	(*i)++;
	if (str[*i] != '\0' && iskey(str[*i]))
		return (handle_var_expansion(str, i, varnames, env));
	else if (str[*i] != '\0' && (str[*i] == '?' || str[*i] == '$'))
	{
		(*i)++;
		return (handle_special_var(str[*i - 1]));
	}
	else if (str[*i] != '\0')
		return (handle_regular_char(i));
	else
		return (1);
}
