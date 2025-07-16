/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:40:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:44:41 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	handle_dollar_char(char *str, size_t *i, char **varnames,
		t_list *env)
{
	(*i)++;
	if (iskey(str[*i]))
		return (handle_var_expansion(str, i, varnames, env));
	else if (str[*i] == '?' || str[*i] == '$')
	{
		(*i)++;
		return (handle_special_var(str[*i - 1]));
	}
	else
		return (handle_regular_char(i));
}
