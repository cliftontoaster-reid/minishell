/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_getenv_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:25:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:26:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include <stdlib.h>

char	*b_getenv_one(char *name, t_list *env)
{
	char	**env_var;
	char	*var_content;

	env_var = b_getenv(name, env);
	if (env_var == NULL || *env_var == NULL)
	{
		return (NULL);
	}
	var_content = *env_var;
	free(env_var);
	return (var_content);
}
