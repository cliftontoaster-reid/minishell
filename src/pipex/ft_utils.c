/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranc <jfranc@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:34:25 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/01 13:35:27 by jfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "pipex.h"

int  ft_nbrofcmds(t_cmd *cmd)
{
	int nbr;

	nbr = 0;
	while (cmd[nbr].args)
		nbr++;
	return (nbr);
}
