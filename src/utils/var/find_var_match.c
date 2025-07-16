/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:25:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:26:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include "utils.h"
#include <stdbool.h>

t_var_match	find_var_match(char *str_pos, char **varnames, t_list *env)
{
	t_var_match	match;
	int			current_var_len;
	int			temp_var_idx;

	match.found = false;
	match.var_len = 0;
	match.value = NULL;
	temp_var_idx = 0;
	while (varnames[temp_var_idx] != NULL)
	{
		current_var_len = ft_strlen(varnames[temp_var_idx]);
		if (ft_strncmp(varnames[temp_var_idx], str_pos, current_var_len) == 0)
		{
			match.value = b_getenv_one(varnames[temp_var_idx], env);
			match.var_len = current_var_len;
			match.found = true;
			break ;
		}
		temp_var_idx++;
	}
	return (match);
}
