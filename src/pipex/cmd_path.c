/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:21:12 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/30 13:38:15 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "pipex.h"

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
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, t_list *tenvp)
{
	t_path_data	pd;

	pd.full_path = NULL;
	pd.paths = ft_split(*b_getenv("PATH", tenvp), ':');
	pd.full_path = ft_check_direct_path(cmd);
	if (pd.full_path)
		return (pd.full_path);
	pd.i = 0;
	while (pd.paths && pd.paths[pd.i])
	{
		pd.tmp = ft_strjoin(pd.paths[pd.i], "/");
		pd.full_path = ft_strjoin(pd.tmp, cmd);
		free(pd.tmp);
		if (access(pd.full_path, X_OK) == 0)
			break ;
		free(pd.full_path);
		pd.full_path = NULL;
		pd.i++;
	}
	ft_free_split(pd.paths);
	return (pd.full_path);
}

/*
int	main(int ac, char **av, char **envp)
{
	char	*argv[] = {"./pipex", "infile", "ls", "-l", NULL};
	int		k = 0;
	char	*s;

	s = ft_get_cmd_path(argv[2], envp);
	ft_printf("%s\n", s);
	free(s);
	return (0);
}
*/
