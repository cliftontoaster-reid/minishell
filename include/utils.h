/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:31:30 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/02 13:24:53 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

typedef struct s_iteration
{
	int				i;
	int				j;
	int				k;
}					t_iteration;

typedef struct s_linereader
{
	char			*line;
	int				fd;
}					t_linereader;

char				*ft_strjoin_free(char *s1, char *s2);

char				*ft_readline(t_linereader *reader);
void				linereader_free(t_linereader *reader);

int					ft_openrand(void);
int					ft_openurand(void);

int					ft_readint(int fd);
long				ft_readlong(int fd);
long long			ft_readlonglong(int fd);

unsigned int		ft_readuint(int fd);
unsigned long		ft_readulong(int fd);
unsigned long long	ft_readullong(int fd);

char				*ft_readstr(int fd, int len);

typedef struct s_file
{
	char			*path;
	int				fd;
}					t_file;

t_file				*ft_opentmp(int rand_fd, bool auto_unlink);

#endif
