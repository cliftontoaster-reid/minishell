/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:21:12 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/28 11:25:01 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "shared.h"
#include <stdbool.h>
#include <unistd.h>
#define CMD_NOT_EXECUTABLE ((char *)-1)


void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

static char	*ft_check_direct_path(char *cmd)
{
	if (!ft_strncmp(cmd, "/", 1) || !ft_strncmp(cmd, "./", 2))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (CMD_NOT_EXECUTABLE);
	}
	return (NULL);
}

static bool	ft_try_path_entry(t_path_data *pd, char *cmd)
{
	pd->tmp = ft_strjoin(pd->paths[pd->i], "/");
	pd->full_path = ft_strjoin(pd->tmp, cmd);
	free(pd->tmp);
	if (access(pd->full_path, X_OK) == 0)
		return (true);
	free(pd->full_path);
	pd->full_path = NULL;
	pd->i++;
	return (false);
}

char	*ft_get_cmd_path(char *cmd, t_list *tenvp)
{
	t_path_data	pd;
	char		**freeleak;

	pd.full_path = ft_check_direct_path(cmd);
	if (pd.full_path == CMD_NOT_EXECUTABLE)
		return (NULL);
	freeleak = b_getenv("PATH", tenvp);
	if (freeleak == NULL)
		return (pd.full_path);
	pd.paths = ft_split(*freeleak, ':');
	free(*freeleak);
	free(freeleak);
	if (pd.full_path)
	{
		ft_free_split(pd.paths);
		return (pd.full_path);
	}
	pd.i = 0;
	while (pd.paths && pd.paths[pd.i])
	{
		if (ft_try_path_entry(&pd, cmd))
			break ;
	}
	ft_free_split(pd.paths);
	return (pd.full_path);
}

/*
int	main(int ac, char **av, char **envp)
{
		char	*argv[] = {"./pipex", "infile", "ls", "-l", NULL};
		int		k;
		char	*s;

		k = 0;
		s = ft_get_cmd_path(argv[2], envp);
		ft_printf("%s\n", s);
		free(s);
		return (0);
}
*/
