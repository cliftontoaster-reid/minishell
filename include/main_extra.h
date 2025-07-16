/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extra.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:41:12 by jfranc            #+#    #+#             */
/*   Updated: 2025/07/16 20:33:10 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_EXTRA_H
# define MAIN_EXTRA_H

# include "libft.h"
# include "parser.h"
# include "shared.h"

/// @brief Prints all tokens in a token list for debugging
/// @param tokens Linked list of tokens to print
void	print_tokens(t_list *tokens);

/// @brief Prints command details for debugging
/// @param cmd Pointer to the command structure to print
void	ft_prints(t_cmd *cmd);

/// @brief Prints parser state and command list for debugging
/// @param parser Pointer to the parser structure to print
void	print_parser(t_parser *parser);

/// @brief Processes heredoc input for parsed commands
/// @param cmds Array of commands to process heredocs for
/// @param env Environment list (currently unused)
void	process_heredocs(t_cmd *cmds, t_list *env);

t_cmd	*remove_empty_commands(t_cmd *commands);

void	print_parser(t_parser *parser);

#endif
