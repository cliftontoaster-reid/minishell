/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:21:12 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/22 13:35:04 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "shared.h"
#include <unistd.h>

void ft_free_split(char **split) {
  int i;

  i = 0;
  if (!split)
    return;
  while (split[i])
    free(split[i++]);
  free(split);
}

static char *ft_check_direct_path(char *cmd) {
  if (ft_strchr(cmd, '/')) {
    if (access(cmd, X_OK) == 0)
      return (ft_strdup(cmd));
    return (NULL);
  }
  return (NULL);
}

char *ft_get_cmd_path(char *cmd, t_list *tenvp) {
  t_path_data pd;
  char **freeleak;

  pd.full_path = NULL;
  freeleak = b_getenv("PATH", tenvp);
  if (freeleak == NULL)
    return (NULL);
  pd.paths = ft_split(*freeleak, ':');
  free(*freeleak);
  free(freeleak);
  pd.full_path = ft_check_direct_path(cmd);
  if (pd.full_path)
    return (pd.full_path);
  pd.i = 0;
  while (pd.paths && pd.paths[pd.i]) {
    pd.tmp = ft_strjoin(pd.paths[pd.i], "/");
    pd.full_path = ft_strjoin(pd.tmp, cmd);
    free(pd.tmp);
    if (access(pd.full_path, X_OK) == 0)
      break;
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
        int		k;
        char	*s;

        k = 0;
        s = ft_get_cmd_path(argv[2], envp);
        ft_printf("%s\n", s);
        free(s);
        return (0);
}
*/
