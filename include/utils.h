/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:31:30 by jfranc            #+#    #+#             */
/*   Updated: 2025/06/18 12:58:36 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_iteration
{
	int		i;
	int		j;
	int		k;
}			t_iteration;

typedef struct s_linereader
{
	char	*line;
	int		fd;
}			t_linereader;

char		*ft_strjoin_free(char *s1, char *s2);

char		*ft_readline(t_linereader *reader);
void		linereader_free(t_linereader *reader);

#endif
