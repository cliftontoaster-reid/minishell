/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:49:37 by jfranc            #+#    #+#             */
/*   Updated: 2025/04/08 16:09:34 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "shared.h"
# include <libft.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define STDIN	0
# define STDOUT	1

typedef struct s_path_data
{
	char	**paths;
	char	*tmp;
	char	*full_path;
	char	*cmd;
	int		i;
}	t_path_data;

typedef struct s_data
{
	char	*cmd_in;
	char	*cmd_out;
	char	**tmp;
	int		fd_infile;
	int		fd_outfile;
	int		fd[2];
	int		pid1;
	int		pid2;
}	t_data;

//cmd_path.c
void	ft_free_split(char **split);
char	*ft_get_cmd_path(char *cmd, t_list *tenvp);

//pipex_utils.c
void	ft_error_exit(char *s);

#endif
