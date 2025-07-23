/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 15:01:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <stdlib.h>

void	remove_env_node(t_list *prev, t_list *current, t_list **envp,
		void (*del)(void *))
{
	if (prev)
		prev->next = current->next;
	else
		*envp = current->next;
	if (del)
		del(current->content);
	else
		free_env_entry(current->content);
	free(current);
}
