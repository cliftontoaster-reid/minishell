/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_substitution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:40:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/16 15:48:17 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	handle_dollar_substitution(t_var_context *ctx)
{
	(*ctx->i)++;
	if (iskey(ctx->src[*ctx->i]))
		return (handle_var_substitution(ctx));
	else if (ctx->src[*ctx->i] == '?' || ctx->src[*ctx->i] == '$')
	{
		ctx->k = expand_special_var(ctx->dest, ctx->src[*ctx->i], ctx->k,
				ctx->len);
		(*ctx->i)++;
		return (ctx->k);
	}
	else
	{
		ctx->dest[ctx->k++] = '$';
		ctx->dest[ctx->k++] = ctx->src[*ctx->i];
		(*ctx->i)++;
		return (ctx->k);
	}
}
