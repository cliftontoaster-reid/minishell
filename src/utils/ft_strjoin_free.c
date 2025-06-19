/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:46:23 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/18 11:56:37 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <errno.h>

static inline char	*handle_null_cases(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	return (NULL);
}

static inline char	*allocate_result(size_t len1, size_t len2, char *s1,
		char *s2)
{
	char	*result;

	result = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!result)
	{
		errno = ENOMEM;
		free(s1);
		free(s2);
	}
	return (result);
}

static inline void	copy_strings(char *result, char *s1, char *s2, size_t len1)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		result[len1 + i] = s2[i];
		i++;
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	char	*null_check;
	size_t	len1;
	size_t	len2;

	null_check = handle_null_cases(s1, s2);
	if (null_check != NULL || (!s1 && !s2))
		return (null_check);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = allocate_result(len1, len2, s1, s2);
	if (!result)
		return (NULL);
	copy_strings(result, s1, s2, len1);
	free(s1);
	free(s2);
	return (result);
}
