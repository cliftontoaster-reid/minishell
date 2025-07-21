/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:40:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/18 11:35:40 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

size_t	handle_var_expansion(char *str, size_t *i, char **varnames, t_list *env)
{
	t_var_match	match;
	size_t		len;

	match = find_var_match(&str[*i], varnames, env);
	if (match.found)
	{
		len = 0;
		if (match.value != NULL)
			len = ft_strlen(match.value);
		*i += match.var_len;
		free(match.value);
		return (len);
	}
	else
	{
		len = count_unmatched_var(str, *i);
		while (iskey(str[*i]))
			(*i)++;
		return (len);
	}
}
