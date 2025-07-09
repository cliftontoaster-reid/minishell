/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varextract.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:27:40 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/09 15:08:16 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"

/// @brief Finds and extracts variable names from a list of tokens.
/// @param tokens Pointer to the list of tokens to process.
/// @return A t_list where each node content is a t_list* of variable name strings for a single command.
t_list	*b_varextract(t_list *tokens);
