/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_substitution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:40:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:48:17 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	handle_var_substitution(t_var_context *ctx)
{
	t_var_match	match;

	match = find_var_match(&ctx->src[*ctx->i], ctx->varnames, ctx->env);
	if (match.found)
	{
		ctx->k = expand_matched_var(ctx->dest, match, ctx->k);
		*ctx->i += match.var_len;
	}
	else
	{
		ctx->k = expand_unmatched_var(ctx->dest, ctx->src, *ctx->i, ctx->k);
		while (iskey(ctx->src[*ctx->i]))
			(*ctx->i)++;
	}
	return (ctx->k);
}
