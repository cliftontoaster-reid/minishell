/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/07/10 14:00:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>

// Helper function to free a single t_cmd structure's dynamically allocated members
static void free_single_cmd(t_cmd *cmd)
{
    if (!cmd)
        return;

    if (cmd->args)
        ft_free_split(cmd->args);
    if (cmd->cmdpathlist)
        ft_free_split(cmd->cmdpathlist);
    if (cmd->redirect_in)
        free(cmd->redirect_in);
    if (cmd->redirect_out)
        free(cmd->redirect_out);
    if (cmd->redirect_append)
        free(cmd->redirect_append);
    if (cmd->redirect_heredoc)
        free(cmd->redirect_heredoc);
    if (cmd->var_list)
        ft_lstclear(&cmd->var_list, free); // Assuming var_list contains dynamically allocated strings
    // Note: cmd->pipes is freed separately in ft_pipex.c
}

// Frees an array of t_cmd structures
void free_commands_array(t_cmd *commands)
{
    size_t i;

    if (!commands)
        return;

    i = 0;
    while (commands[i].args) // Iterate until the sentinel command
    {
        free_single_cmd(&commands[i]);
        i++;
    }
    free(commands);
}
