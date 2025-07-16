/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_varlists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 20:08:13 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "libft.h"

void	free_varlists(t_list *varlists)
{
	t_varexp	varexp;

	varexp.vl_node = varlists;
	while (varexp.vl_node)
	{
		varexp.inner = varexp.vl_node->content;
		ft_lstclear(&varexp.inner, free);
		varexp.next = varexp.vl_node->next;
		free(varexp.vl_node);
		varexp.vl_node = varexp.next;
	}
}
