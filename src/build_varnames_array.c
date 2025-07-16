/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_varnames_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:08:13 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "libft.h"

void	build_varnames_array(t_reader *reader_ptr, t_varexp *varexp)
{
	varexp->vl = (t_list *)varexp->vl_node->content;
	varexp->n = ft_lstsize(varexp->vl);
	reader_ptr->varnames = malloc(sizeof(char *) * (varexp->n + 1));
	if (reader_ptr->varnames)
	{
		varexp->vi = 0;
		varexp->it = varexp->vl;
		while (varexp->it)
		{
			reader_ptr->varnames[varexp->vi++] = varexp->it->content;
			varexp->it = varexp->it->next;
		}
		reader_ptr->varnames[varexp->vi] = NULL;
	}
}
