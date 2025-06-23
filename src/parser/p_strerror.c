/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_strerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:51:55 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/23 10:52:13 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*p_strerror(t_parsing_error error)
{
	switch (error)
	{
	case PARSING_NO_ERROR:
		return ("No error");
	case PARSING_ERROR_MALLOC:
		return ("Memory allocation error");
	case PARSING_MISSING_SPECIAL_TARGET:
		return ("Missing target for special token");
	case PARSING_DOUBLE_SPECIAL_DIRECTIVE:
		return ("Double special directive encountered");
	default:
		return ("Unknown parsing error");
	}
}
