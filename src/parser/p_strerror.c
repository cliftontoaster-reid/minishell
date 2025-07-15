/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_strerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:51:55 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/15 16:17:28 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*p_strerror(t_parsing_error error)
{
	if (error == PARSING_NO_ERROR)
		return ("No error");
	else if (error == PARSING_ERROR_MALLOC)
		return ("Memory allocation error");
	else if (error == PARSING_MISSING_SPECIAL_TARGET)
		return ("Missing target for special token");
	else if (error == PARSING_DOUBLE_SPECIAL_DIRECTIVE)
		return ("Double special directive encountered");
	else
		return ("Unknown parsing error");
}
