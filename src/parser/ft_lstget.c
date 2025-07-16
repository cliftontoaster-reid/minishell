/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:31:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 19:10:30 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

void	*ft_lstget(t_list *lst, size_t n, size_t size)
{
	size_t	i;

	if (!lst)
		return (NULL);
	if (n >= size)
		return (NULL);
	i = 0;
	while (lst && i < n)
	{
		lst = lst->next;
		i++;
	}
	if (lst == NULL)
		return (NULL);
	return (lst->content);
}
