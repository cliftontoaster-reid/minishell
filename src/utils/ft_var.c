/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:30:08 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/15 14:33:57 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"
#include <ctype.h>
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

bool	iskey(char c)
{
	return (isalpha(c) || c == '_');
}

pid_t	b_getpid(void)
{
	int		fd;
	char	buf[64];
	ssize_t	n;
	int		pid;
	char	*p;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	n = read(fd, &buf, 63);
	if (n < 0)
	{
		perror("read");
		close(fd);
		return (-1);
	}
	buf[n] = '\0';
	close(fd);
	pid = 0;
	p = buf;
	while (*p && (*p < '0' || *p > '9'))
	{
		p++;
	}
	while (*p >= '0' && *p <= '9')
	{
		pid = pid * 10 + (*p - '0');
		p++;
	}
	return (pid);
}

int	numPlaces(int n)
{
	int	count;

	if (n == 0)
		return (1);
	if (n < 0)
		n = (n == INT_MIN) ? INT_MAX : -n;
	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*b_getenv_one(char *name, t_list *env)
{
	char	**env_var;
	char	*var_content;

	env_var = b_getenv(name, env);
	if (env_var == NULL || *env_var == NULL)
	{
		return (NULL);
	}
	var_content = *env_var;
	free(env_var);
	return (var_content);
}

size_t	ft_strlen_or_something_i_do_not_know(char *str, char **varnames,
		t_list *env)
{
	size_t	len;
	size_t	i;
	bool	found_match;
	int		current_var_len;
	int		matched_var_name_len;
	char	*env_var;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '$')
		{
			len++;
			i++;
		}
		else
		{
			i++;
			if (iskey(str[i]))
			{
				found_match = false;
				current_var_len = 0;
				matched_var_name_len = 0;
				for (int temp_var_idx = 0; varnames[temp_var_idx] != NULL; temp_var_idx++)
				{
					current_var_len = ft_strlen(varnames[temp_var_idx]);
					if (ft_strncmp(varnames[temp_var_idx], &str[i],
							current_var_len) == 0)
					{
						env_var = b_getenv_one(varnames[temp_var_idx], env);
						if (env_var != NULL)
						{
							len += ft_strlen(env_var);
						}
						matched_var_name_len = current_var_len;
						found_match = true;
						break ;
					}
				}
				if (found_match)
				{
					i += matched_var_name_len;
				}
				else
				{
					len++;
					while (iskey(str[i]))
					{
						len++;
						i++;
					}
				}
			}
			else if (str[i] == '?')
			{
				len += numPlaces(g_status_code);
				i++;
			}
			else if (str[i] == '$')
			{
				len += numPlaces(b_getpid());
				i++;
			}
			else
			{
				len++;
				i++;
			}
		}
	}
	return (len);
}

static void	ft_strcpy(char *dest, const char *src)
{
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
}

char	*ft_var(char *var, char **varnames, t_list *env)
{
	size_t	len;
	char	*owo;
	size_t	i;
	size_t	k;
	bool	found_match;
	int		current_var_len;
	int		matched_var_name_len;
	char	*env_var;

	len = ft_strlen_or_something_i_do_not_know(var, varnames, env);
	owo = malloc(len + 1);
	if (!owo)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	k = 0;
	while (var[i] != '\0')
	{
		if (var[i] != '$')
		{
			owo[k++] = var[i++];
		}
		else
		{
			i++;
			if (iskey(var[i]))
			{
				found_match = false;
				current_var_len = 0;
				matched_var_name_len = 0;
				for (int temp_var_idx = 0; varnames[temp_var_idx] != NULL; temp_var_idx++)
				{
					current_var_len = ft_strlen(varnames[temp_var_idx]);
					if (ft_strncmp(varnames[temp_var_idx], &var[i],
							current_var_len) == 0)
					{
						env_var = b_getenv_one(varnames[temp_var_idx], env);
						if (env_var != NULL)
						{
							ft_strcpy(&owo[k], env_var);
							k += ft_strlen(env_var);
						}
						matched_var_name_len = current_var_len;
						found_match = true;
						break ;
					}
				}
				if (found_match)
				{
					i += matched_var_name_len;
				}
				else
				{
					owo[k++] = '$';
					while (iskey(var[i]))
					{
						owo[k++] = var[i++];
					}
				}
			}
			else if (var[i] == '?')
			{
				k += snprintf(&owo[k], len + 1, "%d", g_status_code);
				i++;
			}
			else if (var[i] == '$')
			{
				k += snprintf(&owo[k], len + 1, "%d", b_getpid());
				i++;
			}
			else
			{
				owo[k++] = '$';
				owo[k++] = var[i++];
			}
		}
	}
	owo[k] = '\0';
	i = 0;
	while (owo[i] != '\0')
	{
		if (owo[i] == '\b')
		{
			owo[i] = '$'; // Replace backspace with dollar sign
		}
		i++;
	}
	free(var);
	return (owo);
}
