/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:31:44 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 12:04:23 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <errno.h>

t_parser	*parser_init(t_list *token_list)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	if (parser == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	parser->token_list = token_list;
	parser->token_count = ft_lstsize(token_list);
	return (parser);
}
