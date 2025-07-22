/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:30:08 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/22 13:41:43 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define VAR_BUFFER_SIZE 128

size_t	ft_strlen_or_something_i_do_not_know(char *str, char **varnames,
		t_list *env)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '$')
			len += handle_regular_char(&i);
		else
			len += handle_dollar_char(str, &i, varnames, env);
	}
	return (len);
}

static void	loopvar(t_var_context *ctx)
{
	if (ctx->src[*(ctx->i)] != '$')
		ctx->k = copy_regular_char(ctx->dest, ctx->src, ctx->i, ctx->k);
	else
		ctx->k = handle_dollar_substitution(ctx);
}

char	*ft_var(char *var, char **varnames, t_list *env)
{
	size_t			len;
	char			*owo;
	size_t			i;
	size_t			k;
	t_var_context	ctx;

	len = ft_strlen_or_something_i_do_not_know(var, varnames, env);
	owo = malloc(len + 1);
	if (!owo)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	k = 0;
	ctx = (t_var_context){owo, var, &i, k, varnames, env, len};
	while (var[i] != '\0')
		loopvar(&ctx);
	owo[len] = '\0';
	replace_backspace_with_dollar(owo);
	free(var);
	return (owo);
}
