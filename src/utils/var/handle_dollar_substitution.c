/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_substitution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:40:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/23 14:56:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static inline bool	is_special_var(char c)
{
	return (c == '?' || c == '$');
}

size_t	handle_dollar_substitution(t_var_context *ctx)
{
	(*ctx->i)++;
	if (ctx->src[*ctx->i] != '\0' && iskey(ctx->src[*ctx->i]))
		return (handle_var_substitution(ctx));
	else if (ctx->src[*ctx->i] != '\0' && is_special_var(ctx->src[*ctx->i]))
	{
		ctx->k = expand_special_var(ctx->dest, ctx->src[*ctx->i], ctx->k,
				ctx->len);
		(*ctx->i)++;
		return (ctx->k);
	}
	else if (ctx->src[*ctx->i] != '\0')
	{
		ctx->dest[ctx->k++] = '$';
		ctx->dest[ctx->k++] = ctx->src[*ctx->i];
		(*ctx->i)++;
		return (ctx->k);
	}
	else
	{
		ctx->dest[ctx->k++] = '$';
		return (ctx->k);
	}
}
