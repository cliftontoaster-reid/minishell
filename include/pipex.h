/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:49:37 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/16 16:02:32 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "shared.h"
# include <fcntl.h>
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1

typedef struct s_path_data
{
	char	**paths;
	char	*tmp;
	char	*full_path;
	char	*cmd;
	int		i;
}			t_path_data;

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
}			t_data;

// cmd_path.c
void		ft_free_split(char **split);
char		*ft_get_cmd_path(char *cmd, t_list *tenvp);

// pipex_utils.c
void		ft_error_exit(char *s);

void		*ft_realloc(void *ptr, size_t size);

#endif
